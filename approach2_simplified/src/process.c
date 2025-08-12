#include "../include/pipex.h"

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

void	process_command(char *cmd, char **envp, int *process_count)
{
	pid_t	pid;
	int		fd[2];

	if (-1 == pipe(fd))
		error_with_message("pipe");
	pid = fork();
	if (-1 == pid)
	{
		close(fd[0]);
		close(fd[1]);
		error_with_message("fork");
	}
	if (0 == pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exe(cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		(*process_count)++;
	}
}
