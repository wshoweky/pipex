#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex_bonus.h"

static int	is_limiter_found(char *line, char *limiter, int limiter_len)
{
	if (ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		return (1);
	return (0);
}

static void	read_heredoc_input(char *limiter, int write_fd)
{
	char	*line;
	int	limiter_len;

	limiter_len = ft_strlen(limiter);
	write(STDOUT_FILENO, "heredoc> ", 9);
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		if (is_limiter_found(line, limiter, limiter_len))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "heredoc> ", 9);
	}	
}

static void	setup_heredoc_child(char *limiter, int *fd)
{
	close(fd[0]);
	read_heredoc_input(limiter, fd[1]);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

static void	setup_heredoc_parent(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	wait(NULL);
}

void	process_heredoc(char *limiter)
{
	pid_t	reader;
	int	fd[2];

	if (-1 == pipe(fd))
		error_with_message("pipe");
	reader = fork();
	if (-1 == reader)
	{
		close (fd[0]);
		close (fd[1]);
		error_with_message ("fork");
	}
	if (0 == reader)
		setup_heredoc_child(limiter, fd);
	else
		setup_heredoc_parent(fd);
}

