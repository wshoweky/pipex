#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "pipex_bonus.h"

#define HEREDOC_YES 1
#define HEREDOC_NO 0

static void	setup_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (-1 == fd)
	{
		perror(filename);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	setup_outfile(char *outfile, int is_heredoc)
{
	int	fd;

	if (is_heredoc == HEREDOC_NO)
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (-1 == fd)
	{
		perror(outfile);
		exit (EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	process_args(int ac, char *av[], char *env[], int is_heredoc)
{
	pid_t	*pids;
	int	pid_count;
	int	i;
	int	max_pids;

	max_pids = ac - (3 + is_heredoc);
	pids = malloc(sizeof(pid_t) * max_pids);
	if (!pids)
		error_with_message("malloc");
	pid_count = 0;
	if (is_heredoc)
		process_heredoc(av[2]);
	i = 2 + is_heredoc;
	while (i < ac - 2)
	{
		process_command(av[i], env, &pids, &pid_count);
		i++;
	}
	setup_outfile(av[ac - 1], is_heredoc);
	wait_for_process(pids, pid_count);
	free(pids);
	exe(av[ac - 2], env);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		show_usage();
		exit (1);
	}
	if ((argc > 5) && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		process_args(argc, argv, envp, HEREDOC_YES);
	}
	else
	{
		setup_infile(argv[1]);
		process_args(argc, argv, envp, HEREDOC_NO);
	}
	return (0);
}
