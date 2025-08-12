/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:30:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 12:30:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	if (!cmd || !*cmd)
		error_exit();
	cmd_args = parse_command(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		if (cmd_args)
			free_array(cmd_args);
		write(STDERR_FILENO, "pipex: command not found\n", 26);
		exit(127);
	}
	if (ft_strchr(cmd_args[0], '/'))
		cmd_path = ft_strdup(cmd_args[0]);
	else
		cmd_path = find_command_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		write(STDERR_FILENO, "pipex: command not found: ", 26);
		write(STDERR_FILENO, cmd_args[0], ft_strlen(cmd_args[0]));
		write(STDERR_FILENO, "\n", 1);
		free_array(cmd_args);
		exit(127);
	}
	execve(cmd_path, cmd_args, envp);
	perror(cmd_path);
	free(cmd_path);
	free_array(cmd_args);
	exit(127);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			break ;
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	**parse_command(char *cmd)
{
	if (!cmd)
		return (NULL);
	return (ft_split(cmd, ' '));
}
