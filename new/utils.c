/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:24:23 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/05 15:50:16 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	error(char *msg)
{
	perror(msg);
	exit(-1);
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
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(pahts[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free(paths[--i]);
	return (NULL);
	//match the cmd from the env pointer
	//using strnstr and strjoin and split!
	//split each env var by ':'
	//join them with '/' and by adding the cmd needed to each path
	//if not found then print error
	//if found then just return it
}

void	exe(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = search_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		error();
	}
	if (-1 == execve(path, cmd, envp))
		error();	
	//search for the path
	//handle errors
	//call execve
	//check that it worked!
}
