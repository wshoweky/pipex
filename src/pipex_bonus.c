#include <complex.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex_bonus.h"

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

static void	setup_outfile(char *outfile, int mode)
{
	int	fd;

	if (0 == mode)
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
		error();
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
		exit (EXIT_FAILURE);
	}
	if ((argc > 5) && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		process_args(argc, argv, envp, 1);
	}
	else
	{
		setup_infile(argv[1]);
		process_args(argc, argv, envp, 0);
	}
	return (0);
}
