/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:30:00 by wsm               #+#    #+#             */
/*   Updated: 2024/08/11 12:30:00 by wsm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define BUFFER_SIZE 1024

static char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
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

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	len1 = s1 ? ft_strlen(s1) : 0;
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1 && i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*temp;
	int		line_len;
	int		i;

	if (!*buffer || !**buffer)
		return (NULL);
	newline_pos = ft_strchr_gnl(*buffer, '\n');
	if (newline_pos)
		line_len = newline_pos - *buffer + 1;
	else
		line_len = ft_strlen(*buffer);
	line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = (*buffer)[i];
		i++;
	}
	line[i] = '\0';
	if (newline_pos)
		temp = ft_strdup(newline_pos + 1);
	else
		temp = NULL;
	free(*buffer);
	*buffer = temp;
	return (line);
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer = NULL;
	char		read_buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	while (!ft_strchr_gnl(buffer, '\n'))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		read_buffer[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, read_buffer);
		if (!buffer)
			return (-1);
	}
	*line = extract_line(&buffer);
	if (!*line)
		return (0);
	return (1);
}
