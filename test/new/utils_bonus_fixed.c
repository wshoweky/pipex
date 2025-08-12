/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus_fixed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:45:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 11:45:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

/* Enhanced usage function with better formatting */
void	usage(void)
{
	ft_dprintf(STDERR_FILENO, "\033[31mError: Bad argument\033[0m\n");
	ft_dprintf(STDERR_FILENO, "\033[33mUsage:\033[0m\n");
	ft_dprintf(STDERR_FILENO, "  ./pipex <infile> <cmd1> <cmd2> [cmd3...] <outfile>\n");
	ft_dprintf(STDERR_FILENO, "  ./pipex here_doc <LIMITER> <cmd1> <cmd2> [cmd3...] <outfile>\n");
	ft_dprintf(STDERR_FILENO, "\033[36mExamples:\033[0m\n");
	ft_dprintf(STDERR_FILENO, "  ./pipex input.txt \"grep hello\" \"wc -l\" output.txt\n");
	ft_dprintf(STDERR_FILENO, "  ./pipex here_doc EOF \"cat -n\" \"wc -l\" output.txt\n");
	exit(EXIT_FAILURE);
}

/* Enhanced file opening with better error handling */
int	open_file(char *filename, int mode)
{
	int	file;

	if (mode == 0)  // Append mode (for heredoc)
		file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)  // Truncate mode (for regular output)
		file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)  // Read mode (for input)
		file = open(filename, O_RDONLY);
	else
	{
		ft_dprintf(STDERR_FILENO, "pipex: internal error: invalid file mode\n");
		exit(EXIT_FAILURE);
	}

	if (file == -1)
	{
		perror(filename);
		exit(EXIT_FAILURE);
	}

	return (file);
}

/* These functions are now handled by libft's ft_strlcpy and ft_strlcat */

/* Free string array utility */
bool	free_str_arr(char **arr)
{
	int	i;

	if (!arr)
		return (false);
	
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (true);
}

/* Debug function to trace execution (can be removed in final version) */
void	debug_msg(char *msg)
{
	if (getenv("PIPEX_DEBUG"))
		ft_dprintf(STDERR_FILENO, "[DEBUG] %s\n", msg);
}
