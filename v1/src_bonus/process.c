/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:58:10 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/14 16:16:21 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
** Waits for all child processes to complete
** Takes the number of processes to wait for
** Uses wait() to collect exit status and prevent zombies
*/
void	wait_for_all_processes(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		wait(NULL);
		i++;
	}
}

/*
** Waits for all processes including the last one
** Returns the exit status of the last command
** Ensures proper handling of exit status
*/
int	wait_for_processes(int count, pid_t last_pid)
{
	int		i;
	int		status;
	int		exit_status;
	pid_t	pid;

	i = 0;
	exit_status = 0;
	
	/* Wait for intermediate processes */
	while (i < count)
	{
		wait(NULL);
		i++;
	}
	
	/* Wait for the last process and get its exit status */
	pid = waitpid(last_pid, &status, 0);
	if (pid == last_pid && WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	
	return (exit_status);
}

/*
** Closes all file descriptors and exits with an error
** Used when a fork fails to clean up resources
*/
static void	close_all(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	system_call_error("fork");
}

/*
** Processes a single command in the pipeline
** Creates a pipe and forks a child process
** Child process executes the command
** Parent process sets up the next command in the pipeline
** Increments the process count for proper waiting
*/
void	process_command(char *cmd, char **en, int *process_count)
{
	pid_t	pid;
	int		fd[2];

	if (-1 == pipe(fd))
		system_call_error("pipe");
	pid = fork();
	if (-1 == pid)
		close_all(fd);
	if (0 == pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exe(cmd, en);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		(*process_count)++;
	}
}
