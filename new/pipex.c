/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:48:59 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/05 11:26:44 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include "pipex.h"

void	sub_proc(char **argv, char **envp, int pipe_fd)
{
	//open infile 0644
	//error check
	//dup2 i/o & close
	//call exe
}

void	original_proc(char **argv, char **envp, int pipe_fd)
{

}

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if(-1 == pipe(pipe_fd))
			error();
		pid = fork();
		if (-1 == pid)
			error();
		if (0 == pid)
			//sub_proc
		if (pid)
			//original_proc

	}
	else
	{
		perror ("Wrong Argument!\n");
	}
	return (-1);
}
