#include "pipex_bonus.h"

t_pid_manager	*init_pid_manager(int capacity)
{
	t_pid_manager	*pid_mgr;

	if (capacity <= 0)
		return (NULL);
	
	pid_mgr = malloc(sizeof(t_pid_manager));
	if (!pid_mgr)
		return (NULL);
	
	pid_mgr->pids = malloc(sizeof(pid_t) * capacity);
	if (!pid_mgr->pids)
	{
		free(pid_mgr);
		return (NULL);
	}
	
	pid_mgr->count = 0;
	pid_mgr->capacity = capacity;
	return (pid_mgr);
}

void	add_pid(t_pid_manager *pid_mgr, pid_t pid)
{
	if (!pid_mgr || pid_mgr->count >= pid_mgr->capacity)
		return;
	
	pid_mgr->pids[pid_mgr->count] = pid;
	pid_mgr->count++;
}

void	cleanup_pid_manager(t_pid_manager *pid_mgr)
{
	if (!pid_mgr)
		return;
	
	if (pid_mgr->pids)
		free(pid_mgr->pids);
	
	free(pid_mgr);
}
