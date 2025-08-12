#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex_bonus.h"

void	wait_for_process(t_pid_manager *pid_mgr)
{
	int	i;
	int	status;

	if (!pid_mgr || !pid_mgr->pids || pid_mgr->count <= 0)
		return;
	
	i = 0;
	while (i < pid_mgr->count)
	{
		waitpid(pid_mgr->pids[i], &status, 0);
		i++;
	}
}

void	process_command(char *cmd, char **envp, t_pid_manager *pid_mgr)
{
	pid_t	pid;
	int		fd[2];

	/* Validate parameters */
	if (!cmd || !envp || !pid_mgr)
		error_with_cleanup("process_command: invalid parameters", pid_mgr);

	if (-1 == pipe(fd))
		error_with_cleanup("pipe", pid_mgr);
	
	pid = fork();
	if (-1 == pid)
	{
		close(fd[0]);
		close(fd[1]);
		error_with_cleanup("fork", pid_mgr);
	}
	
	if (0 == pid)
	{
		/* Child process - execute command */
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exe(cmd, envp);
		/* exe never returns, but if it does, exit with error */
		error_with_message("exe failed");
	}
	else
	{
		/* Parent process - store pid and continue */
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		
		/* Store the child process ID */
		add_pid(pid_mgr, pid);
	}
}
