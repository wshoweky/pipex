#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	next_line = gnl_strjoin (0, buffer);
	if (gnl_clean(buffer) > 0)
		return (next_line);
	i = read (fd, buffer, BUFFER_SIZE);
	if (i < 0)
	{
		free (next_line);
		return (0);
	}
	buffer[i] = '\0';
	while (i > 0)
	{
		next_line = gnl_strjoin(next_line, buffer);
		if (gnl_clean(buffer) > 0)
			return (next_line);
		i = read(fd, buffer, BUFFER_SIZE);
	}
	return (next_line);
}
