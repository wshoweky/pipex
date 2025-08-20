/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:12:47 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/18 11:12:51 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Handles the first command in the pipeline (cmd1)
** Opens the input file and connects it to stdin
** Redirects stdout to the write end of the pipe
** Executes the first command
*/
static void	first_child(int *pipe_fd, char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (-1 == infile)
	{
		print_file_error(argv[1]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
		system_call_error("dup2");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		system_call_error("dup2");
	close(infile);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	exe(argv[2], envp);
}

/*
** Handles the second command in the pipeline (cmd2)
** Opens the output file and connects it to stdout
** Redirects stdin to the read end of the pipe
** Executes the second command
*/
static void	second_child(int *pipe_fd, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (-1 == outfile)
	{
		print_file_error(argv[4]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
		system_call_error("dup2");
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		system_call_error("dup2");
	close(outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exe(argv[3], envp);
}

/*
** Creates two child processes for the pipeline
** First child handles the first command (cmd1)
** Second child handles the second command (cmd2)
** Stores the PIDs in the pids array for later use
*/
static void	create_children(int *pipe_fd, char **argv, char **envp, pid_t *pids)
{
	pids[0] = fork();
	if (-1 == pids[0])
		system_call_error("fork");
	if (0 == pids[0])
		first_child(pipe_fd, argv, envp);
	pids[1] = fork();
	if (-1 == pids[1])
		system_call_error("fork");
	if (0 == pids[1])
		second_child(pipe_fd, argv, envp);
}

/*
** Waits for both child processes to complete
** Uses waitpid(-1, ...) to avoid zombie processes
** Returns the exit status of the second command (pid2)
** This follows the POSIX standard for pipelines
*/
static int	wait_for_children(pid_t pid2)
{
	int		status;
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) && pid == pid2)
		exit_status = WEXITSTATUS(status);
	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) && pid == pid2)
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

/*
** Main function for the pipex program
** Validates arguments, creates a pipe, and sets up the pipeline
** Creates two child processes for cmd1 and cmd2
** Waits for both processes and returns the exit status
** Usage: ./pipex file1 cmd1 cmd2 file2
*/
int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pids[2];
	int		exit_status;

	if (5 != argc)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	if (-1 == pipe(pipe_fd))
		system_call_error("pipe");
	create_children(pipe_fd, argv, envp, pids);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit_status = wait_for_children(pids[1]);
	return (exit_status);
}
