#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

/* Struct to manage process IDs and memory */
typedef struct s_pid_manager
{
	pid_t	*pids;
	int		count;
	int		capacity;
}	t_pid_manager;

/* Function declarations */
void	error_with_message(const char *message);
void	error_with_cleanup(const char *message, t_pid_manager *pid_mgr);
void	show_usage(void);
void	ft_free(char **ptr);
char	*search_path(char *cmd, char **envp);
void	exe(char *argv, char **envp);
void	process_heredoc(char *limiter);
void	process_command(char *cmd, char **envp, t_pid_manager *pid_mgr);
void	wait_for_process(t_pid_manager *pid_mgr);

/* PID manager functions */
t_pid_manager	*init_pid_manager(int capacity);
void			add_pid(t_pid_manager *pid_mgr, pid_t pid);
void			cleanup_pid_manager(t_pid_manager *pid_mgr);

#endif
