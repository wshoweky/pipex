/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:44:35 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/08 14:29:44 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sub_process(int *pipe_fd, char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (-1 == infile)
		error_with_message(argv[1]);
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(infile);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	exe(argv[2], envp);
}

void	original_process(int *pipe_fd, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == outfile)
		error_with_message(argv[4]);
	dup2(outfile, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exe(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	if (argc != 5)
	{
		ft_printf("Usage: file1 cmd1 cmd2 file2\n");
		return (-1);
	}
	if (-1 == pipe(pipe_fd))
		error_with_message("Error: pipe\n");
	pid = fork();
	if (-1 == pid)
		error_with_message("Error: fork\n");
	if (0 == pid)
		sub_process(pipe_fd, argv, envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (WEXITSTATUS(status));
	original_process(pipe_fd, argv, envp);
	return (0);
}
