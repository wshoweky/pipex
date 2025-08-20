/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:31:11 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/18 12:13:40 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
** Executes a command with the given arguments and environment
** Splits the command string into arguments
** Finds the full path to the command executable
** Executes the command using execve
** Handles any errors that occur during execution
*/
static void	handle_cmd_errors(char **cmd)
{
	if (!cmd || !cmd[0] || !*cmd[0])
	{
		if (cmd)
			ft_free(cmd);
		print_command_error("");
		exit(127);
	}
}

void	exe(char *av, char **en)
{
	char	**cmd;
	char	*path;

	if (!av || !en || !*av)
	{
		print_command_error("");
		exit(127);
	}
	cmd = ft_split(av, ' ');
	handle_cmd_errors(cmd);
	if (ft_strchr(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else
		path = search_path(cmd[0], en);
	if (!path)
	{
		print_command_error(cmd[0]);
		ft_free(cmd);
		exit(127);
	}
	execve(path, cmd, en);
	handle_execve_error(path, cmd);
}
