/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:12:29 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/18 11:12:32 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Searches for a command in the directories specified in paths
** For each directory, creates a full path and checks if it exists
** Returns the full path if found, NULL otherwise
** Frees the paths array before returning
*/
static char	*try_path_locations(char **paths, char *cmd)
{
	char	*path;
	char	*part_path;
	int		i;

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

/*
** Searches for a command in the PATH environment variable
** First checks if the command exists in the current directory
** Then searches in each directory in the PATH
** Returns the full path to the command if found, NULL otherwise
*/
char	*search_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (try_path_locations(paths, cmd));
}

/*
** Handles errors related to command validation
** Checks if the command is empty or doesn't exist
** Prints appropriate error messages and exits with code 127
** Frees allocated memory before exiting
*/
static void	handle_cmd_errors(char **cmd, char *path)
{
	if (!cmd[0] || !cmd[0][0])
	{
		print_command_error("");
		ft_free(cmd);
		exit(127);
	}
	if (!path)
	{
		print_command_error(cmd[0]);
		ft_free(cmd);
		exit(127);
	}
}

/*
** Gets the full path to a command
** If the command contains a path separator (/), uses it directly
** Otherwise searches for the command in the PATH
** Returns the full path if found, exits with error if not
*/
static char	*get_cmd_path(char **cmd, char **envp)
{
	char	*path;

	if (ft_strchr(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else
		path = search_path(cmd[0], envp);
	if (!path)
	{
		print_command_error(cmd[0]);
		ft_free(cmd);
		exit(127);
	}
	return (path);
}

/*
** Executes a command with the given arguments and environment
** Splits the command string into arguments
** Finds the full path to the command executable
** Executes the command using execve
** Handles any errors that occur during execution
*/
void	exe(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (!argv || !argv[0])
	{
		print_command_error("");
		exit(127);
	}
	if (!envp)
		system_call_error("invalid environment");
	cmd = ft_split(argv, ' ');
	if (!cmd)
		system_call_error("ft_split failed");
	handle_cmd_errors(cmd, cmd[0]);
	path = get_cmd_path(cmd, envp);
	execve(path, cmd, envp);
	handle_execve_error(path, cmd);
}
