/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:30:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 12:30:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_command(char *cmd, char **envp, pid_t **pids, int *count)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_exit();
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error_exit();
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command(cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		(*pids)[*count] = pid;
		(*count)++;
	}
}

void	wait_for_processes(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
}


