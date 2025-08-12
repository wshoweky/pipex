#include "../include/pipex.h"

void	exe(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (!argv || !envp || !*argv)
		error_with_message("Error: invalid arguments");
	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0] || !*cmd[0])
	{
		if (cmd)
			ft_free(cmd);
		error_with_message("Error: empty command");
	}
	path = search_path(cmd[0], envp);
	if (!path)
	{
		ft_free(cmd);
		error_with_message("Error: command not found");
	}
	execve(path, cmd, envp);
	free(path);
	ft_free(cmd);
	error_with_message("Error: execve failed");
}
