#include "../include/pipex.h"

void	error_with_message(const char *msg)
{
	if (msg)
		perror(msg);
	else
		perror("Error");
	exit(EXIT_FAILURE);
}

void	show_usage(void)
{
	write(STDERR_FILENO, "Usage:\n", 7);
	write(STDERR_FILENO, "  ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 42);
	write(STDERR_FILENO, "  ./pipex here_doc <LIMITER> <cmd1> <cmd2> ", 42);
	write(STDERR_FILENO, "<outfile>\n", 10);
}

void	ft_free(char **ptr)
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

	if (!cmd || !*cmd || !envp)
		return (NULL);
	i = 0;
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
			ft_free(paths);
			return (NULL);
		}
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!path)
		{
			ft_free(paths);
			return (NULL);
		}
		if (access(path, F_OK) == 0)
		{
			ft_free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}
