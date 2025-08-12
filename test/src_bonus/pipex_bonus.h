#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

void	ft_free(char **ptr);
void	error_with_message(const char *msg);
void	exe(char *argv, char **envp);
void	process_heredoc(char *limiter);
void	process_command(char *cmd, char **envp, pid_t **pids, int *count);
void	wait_for_process(pid_t *pids, int count);
void	show_usage(void);
char	*search_path(char *cmd, char **envp);

#endif
