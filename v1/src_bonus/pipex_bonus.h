/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:00:02 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/14 16:16:08 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"

/* Function prototypes */
void	ft_free(char **ptr);
void	error_with_message(const char *msg);
void	exe(char *argv, char **envp);
void	process_heredoc(char *limiter);
void	process_command(char *cmd, char **envp, int *process_count);
void	wait_for_all_processes(int count);
int		wait_for_processes(int count, pid_t last_pid);
void	show_usage(void);
char	*search_path(char *cmd, char **envp);

/* Error handling functions */
void	print_file_error(const char *filename);
void	system_call_error(const char *message);
void	logic_error(const char *message);
void	print_command_error(const char *command);
void	handle_execve_error(char *path, char **args);

#endif
