/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:30:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 12:30:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Function prototypes */
void	error_exit(void);
void	execute_command(char *cmd, char **envp);
void	process_command(char *cmd, char **envp, pid_t **pids, int *count);
void	handle_heredoc(char *limiter, int argc);
void	wait_for_processes(pid_t *pids, int count);
int		open_file(char *filename, int mode);
void	show_usage(void);
char	**parse_command(char *cmd);
char	*find_command_path(char *cmd, char **envp);
char	**get_paths(char **envp);
void	free_array(char **arr);
int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);

#endif
