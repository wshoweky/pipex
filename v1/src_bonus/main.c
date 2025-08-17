/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:48:58 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/14 16:16:02 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
** Sets up the input file for the pipeline
** Opens the file and redirects stdin to it
** Exits with error if the file cannot be opened
*/
static void	setup_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (-1 == fd)
	{
		print_file_error(filename);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/*
** Sets up the output file for the pipeline
** Opens the file with appropriate flags based on heredoc mode
** Redirects stdout to the file
** Exits with error if the file cannot be opened
*/
static void	setup_outfile(char *outfile, int is_heredoc)
{
	int	fd;

	if (is_heredoc)
		fd = open (outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open (outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == fd)
	{
		print_file_error(outfile);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/*
** Processes the command line arguments
** Sets up heredoc or input file
** Processes each command in the pipeline
** Sets up the output file
** Waits for all processes to complete
** Executes the last command
** Returns the exit status of the last command
*/
static int	process_args(int ac, char **av, char **en, int is_heredoc)
{
	int		process_count;
	int		i;
	int		exit_status;
	pid_t	last_pid;

	process_count = 0;
	if (is_heredoc)
		process_heredoc(av[2]);
	i = 2 + is_heredoc;
	while (i < ac - 2)
		process_command(av[i++], en, &process_count);
	setup_outfile(av[ac - 1], is_heredoc);
	/* Execute the last command */
	last_pid = fork();
	if (last_pid == -1)
		system_call_error("fork");
	if (last_pid == 0)
		exe(av[ac - 2], en);
	/* Wait for all processes and get the exit status */
	exit_status = wait_for_processes(process_count, last_pid);
	return (exit_status);
}

/*
** Main function for the pipex bonus program
** Validates arguments and checks for heredoc mode
** Sets up the pipeline based on the arguments
** Supports multiple commands and heredoc
** Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2
**        ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2
** Returns the exit status of the last command
*/
int	main(int ac, char **av, char **en)
{
	int	exit_status;

	if (ac < 5)
	{
		show_usage();
		exit(EXIT_FAILURE);
	}
	if ((ac > 5) && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		exit_status = process_args(ac, av, en, 1);
	}
	else
	{
		setup_infile(av[1]);
		exit_status = process_args(ac, av, en, 0);
	}
	return (exit_status);
}
