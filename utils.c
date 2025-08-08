/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:48:59 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/08 14:28:43 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_with_message(const char *message)
{
	if (message)
		perror(message);
	else
		perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_free(void **ptr)
{
	int	i;

	i = 0;
	if (!ptr || !*ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

char	*search_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			ft_free((void **)paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free((void **)paths);
	return (NULL);
}

void	exe(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error_with_message("Error: memory allocation\n");
	path = search_path(cmd[0], envp);
	if (!path)
	{
		ft_free((void **)cmd);
		error_with_message("Error: File does not exist (ENOENT)\n");
	}
	if (-1 == execve(path, cmd, envp))
	{
		free(path);
		ft_free((void **)cmd);
		error_with_message("Error: execve failed\n");
	}
}
