/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:27:12 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/18 11:23:05 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

//prototypes!
void	exe(char *argv, char **envp);
void	ft_free(char **ptr);
char	*search_path(char *cmd, char **envp);

// Enhanced error handling functions
void	print_file_error(const char *filename);
void	system_call_error(const char *message);
void	print_command_error(const char *command);
void	handle_execve_error(char *path, char **args);

#endif
