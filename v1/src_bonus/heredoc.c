/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:08:51 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/14 16:14:22 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
** Checks if the current line matches the heredoc limiter
** Returns 1 if the line matches the limiter, 0 otherwise
*/
static int	is_limiter_found(char *line, char *limiter, int limiter_len)
{
	if (ft_strncmp(line, limiter, limiter_len) == 0
		&& line[limiter_len] == '\n')
		return (1);
	return (0);
}

/*
** Reads input from stdin until the limiter is found
** Writes each line to the pipe for the next command
** Frees each line after processing
*/
static void	read_heredoc_input(char *limiter, int write_fd)
{
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	write(STDOUT_FILENO, "here_doc> ", 10);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (is_limiter_found(line, limiter, limiter_len))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
	}
}

/*
** Sets up the child process for heredoc
** Closes the read end of the pipe
** Reads input until the limiter is found
** Exits with success status
*/
static void	setup_heredoc_child(char *limiter, int *fd)
{
	close(fd[0]);
	read_heredoc_input(limiter, fd[1]);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

/*
** Sets up the parent process for heredoc
** Closes the write end of the pipe
** Redirects stdin to the read end of the pipe
** Waits for the child process to finish
*/
static void	setup_heredoc_parent(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	wait(NULL);
}

/*
** Processes heredoc input for the pipeline
** Creates a pipe and forks a child process
** Child reads input until the limiter is found
** Parent redirects stdin to the read end of the pipe
*/
void	process_heredoc(char *limiter)
{
	pid_t	reader;
	int		fd[2];

	if (-1 == pipe(fd))
		system_call_error("pipe");
	reader = fork();
	if (-1 == reader)
	{
		close(fd[0]);
		close(fd[1]);
		system_call_error("fork");
	}
	if (0 == reader)
		setup_heredoc_child(limiter, fd);
	else
		setup_heredoc_parent(fd);
}
