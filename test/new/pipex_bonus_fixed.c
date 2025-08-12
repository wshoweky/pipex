/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_fixed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:40:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 11:40:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

/* Global variable to count child processes */
static int	g_child_count = 0;

/* Error handling function */
void	error(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

/* Execute command with PATH resolution */
void	execute(char *cmd, char **envp)
{
	char	**cmd_args;

	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd)
		error();
	
	// Parse command arguments
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		if (cmd_args)
			free_str_arr(cmd_args);
		ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", cmd);
		exit(127);
	}

	// If command has '/', use it directly
	if (ft_strchr(cmd_args[0], '/'))
	{
		execve(cmd_args[0], cmd_args, envp);
		perror(cmd_args[0]);
		free_str_arr(cmd_args);
		exit(127);
	}

	// Find command in PATH
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	
	if (!envp[i])
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", cmd_args[0]);
		free_str_arr(cmd_args);
		exit(127);
	}

	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		error();

	i = 0;
	while (paths[i])
	{
		full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd_args[0]) + 2);
		if (!full_path)
			error();
		
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + ft_strlen(cmd_args[0]) + 2);
		ft_strlcat(full_path, "/", ft_strlen(paths[i]) + ft_strlen(cmd_args[0]) + 2);
		ft_strlcat(full_path, cmd_args[0], ft_strlen(paths[i]) + ft_strlen(cmd_args[0]) + 2);
		
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, cmd_args, envp);
			// If we get here, execve failed
			perror(full_path);
			free(full_path);
			free_str_arr(paths);
			free_str_arr(cmd_args);
			exit(127);
		}
		free(full_path);
		i++;
	}

	// Command not found in PATH
	ft_dprintf(STDERR_FILENO, "pipex: %s: command not found\n", cmd_args[0]);
	free_str_arr(paths);
	free_str_arr(cmd_args);
	exit(127);
}

/* Fixed child_process: creates pipe and forks, but doesn't wait immediately */
void	child_process(char *cmd, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error();
	}
	
	if (pid == 0)  // Child process
	{
		close(fd[0]);  // Close read end
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);  // Close after dup2
		execute(cmd, envp);
	}
	else  // Parent process
	{
		close(fd[1]);  // Close write end
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);  // Close after dup2
		g_child_count++;  // Count this child
		// DON'T wait here - let it run in parallel!
	}
}

/* Fixed heredoc: proper memory management and delimiter checking */
void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;
	int		limiter_len;

	if (argc < 6)
	{
		ft_dprintf(STDERR_FILENO, "Error: Bad argument\n");
		ft_dprintf(STDERR_FILENO, "Usage: ./pipex here_doc <LIMITER> <cmd1> <cmd2> <...> <file>\n");
		exit(EXIT_FAILURE);
	}

	if (pipe(fd) == -1)
		error();

	reader = fork();
	if (reader == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error();
	}

	if (reader == 0)  // Child: read from stdin
	{
		close(fd[0]);  // Close read end
		limiter_len = ft_strlen(limiter);
		
		ft_dprintf(STDOUT_FILENO, "heredoc> ");  // Prompt user
		while (set_next_line(STDIN_FILENO, &line))
		{
			if (!line)
				break;
				
			// Check if line matches limiter (with newline)
			if ((int)ft_strlen(line) == limiter_len + 1 && 
				ft_strncmp(line, limiter, limiter_len) == 0 && 
				line[limiter_len] == '\n')
			{
				free(line);
				break;
			}
			
			write(fd[1], line, ft_strlen(line));
			free(line);
			ft_dprintf(STDOUT_FILENO, "heredoc> ");  // Next prompt
		}
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else  // Parent: prepare to read from pipe
	{
		close(fd[1]);  // Close write end
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);  // Wait for heredoc reader to finish
	}
}

/* Wait for all child processes */
void	wait_for_all_children(void)
{
	int	status;
	
	while (g_child_count > 0)
	{
		wait(&status);
		g_child_count--;
	}
}

/* Main function with fixed process management */
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc < 5)
	{
		ft_dprintf(STDERR_FILENO, "Error: Bad argument\n");
		ft_dprintf(STDERR_FILENO, "Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n");
		ft_dprintf(STDERR_FILENO, "    ./pipex here_doc <LIMITER> <cmd> <cmd1> <...> <file>\n");
		exit(EXIT_FAILURE);
	}

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		// Heredoc mode
		i = 3;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fileout == -1)
			error();
		here_doc(argv[2], argc);
	}
	else
	{
		// Regular file input mode
		i = 2;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fileout == -1)
			error();
		filein = open(argv[1], O_RDONLY);
		if (filein == -1)
		{
			perror(argv[1]);
			// Continue anyway - let the command handle the error
		}
		else
		{
			dup2(filein, STDIN_FILENO);
			close(filein);
		}
	}

	// Process all middle commands (create parallel pipeline)
	while (i < argc - 2)
		child_process(argv[i++], envp);

	// Set up output for last command
	dup2(fileout, STDOUT_FILENO);
	close(fileout);

	// Wait for all middle commands to finish
	wait_for_all_children();

	// Execute the last command
	execute(argv[argc - 2], envp);

	return (0);  // Should never reach here
}
