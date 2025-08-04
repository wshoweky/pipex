#include <complex.h>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include "pipex.h"

void	ft_error(void)
{
	perror("smth!\n");
	exit(EXIT_FAILURE);
}

//TODO ft_free

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
		//can we get away with only one var path?! join returns alloc ptr
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free(paths[--i]);
	return (NULL);
}

void	exe(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, 32);
	path = search_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		ft_error();
	}
	//is execve gonna free path later??
	if (-1 == execve(path, cmd, envp))
		ft_error();
}

