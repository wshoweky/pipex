/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:30:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 12:30:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

void	show_usage(void)
{
	write(STDERR_FILENO, "Usage:\n", 7);
	write(STDERR_FILENO, "  ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 42);
	write(STDERR_FILENO, "  ./pipex here_doc <LIMITER> <cmd1> <cmd2> ", 42);
	write(STDERR_FILENO, "<outfile>\n", 10);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
