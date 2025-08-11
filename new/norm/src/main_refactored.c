/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_refactored.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:00:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 13:00:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setup_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	setup_output_file(char *filename, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/* 
** Combined function that handles both regular and heredoc pipelines
** is_heredoc: 1 for heredoc mode, 0 for regular mode
*/
static void	process_commands(int argc, char **argv, char **envp, int is_heredoc)
{
	pid_t	*pids;
	int		pid_count;
	int		i;
	int		max_pids;

	max_pids = argc - (3 + is_heredoc);
	pids = malloc(sizeof(pid_t) * max_pids);
	if (!pids)
		error_exit();
	pid_count = 0;
	if (is_heredoc)
		handle_heredoc(argv[2], argc);
	i = 2 + is_heredoc;
	while (i < argc - 2)
	{
		process_command(argv[i], envp, &pids, &pid_count);
		i++;
	}
	setup_output_file(argv[argc - 1], !is_heredoc);
	wait_for_processes(pids, pid_count);
	free(pids);
	execute_command(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		show_usage();
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			show_usage();
			exit(EXIT_FAILURE);
		}
		process_commands(argc, argv, envp, 1);
	}
	else
	{
		setup_input_file(argv[1]);
		process_commands(argc, argv, envp, 0);
	}
	return (0);
}
