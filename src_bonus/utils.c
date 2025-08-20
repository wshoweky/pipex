/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshoweky <wshoweky@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:39:19 by wshoweky          #+#    #+#             */
/*   Updated: 2025/08/18 11:38:36 by wshoweky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
** Displays usage information for the program
** Shows how to use the program with regular files
** Shows how to use the program with heredoc
*/
void	show_usage(void)
{
	write(STDERR_FILENO, "Usage:\n", 7);
	write(STDERR_FILENO, "  ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 42);
	write(STDERR_FILENO, "  ./pipex here_doc <LIMITER> <cmd1> <cmd2> ", 42);
	write(STDERR_FILENO, "<outfile>\n", 10);
}

/*
** Frees a NULL-terminated array of strings and the array itself
** Safely handles NULL pointers and empty arrays
** Used to free memory allocated by functions like ft_split
*/
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

/*
** Searches for a command in the PATH environment variable
** First checks if the command exists in the current directory
** Then searches in each directory in the PATH
** Returns the full path to the command if found, NULL otherwise
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

char	*search_path(char *cmd, char **en)
{
	char	**paths;
	int		i;

	if (!cmd || !*cmd || !en)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (en[i] && ft_strnstr(en[i], "PATH", 4) == NULL)
		i++;
	if (!en[i])
		return (NULL);
	paths = ft_split(en[i] + 5, ':');
	return (try_path_locations(paths, cmd));
}
