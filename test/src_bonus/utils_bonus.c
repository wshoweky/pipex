#include "pipex_bonus.h"

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
	write(STDERR_FILENO, "  ./pipex_bonus <infile> <cmd1> <cmd2> <outfile>\n", 50);
	write(STDERR_FILENO, "  ./pipex_bonus here_doc <LIMITER> <cmd1> <cmd2> ", 50);
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
	int	i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths && paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
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

void	exe(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (!argv || !envp)
		error_with_message("Error: invalid arguments");
	cmd = ft_split(argv, ' ');
	if (!cmd)
		error_with_message("Error: memory allocation");
	path = search_path(cmd[0], envp);
	if(!path)
	{
		ft_free(cmd);
		error_with_message("Error: file does not exist (ENOENT)");
	}
	if (-1 == execve(path, cmd, envp))
	{
		free(path);
		ft_free(cmd);
		error_with_message("Error: execve failed");
	}
}
