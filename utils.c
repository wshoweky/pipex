#include "pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	error_with_message(const char *message)
{
	if (message)
	{
		fprintf(stderr, "%s\n", message); //, strerror(errno));
		fflush(stderr);
	}
	else
	{
		perror("Error");
		fflush(stderr);
	}
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
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
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
		{
			ft_free((void **)paths);
			return (NULL);
		}
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!path)
		{
			ft_free((void **)paths);
			return (NULL);
		}
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
		error_with_message("memory allocation");
	path = search_path(cmd[0], envp);
	if (!path)
	{
		ft_free((void **)cmd);
		//errno = ENOENT;  // No such file or directory		
		error_with_message("command not found");
	}
	if (-1 == execve(path, cmd, envp))
	{
		free(path);
		ft_free((void **)cmd);
		error_with_message(cmd[0]);
	}
}

