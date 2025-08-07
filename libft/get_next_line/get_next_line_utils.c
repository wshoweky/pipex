#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	ln;

	ln = 0;
	while (str && str[ln] && str[ln] != '\n')
		ln++;
	if (str && str[ln] == '\n')
		ln++;
	return (ln);
}

int	gnl_clean(char *str)
{
	int	i;
	int	n;
	int	is_nl;

	i = 0;
	n = 0;
	is_nl = 0;
	while (str && str[i])
	{
		if (is_nl)
			str[n++] = str[i];
		if (str[i] == '\n')
			is_nl = 1;
		str[i++] = '\0';
	}
	return (is_nl);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*next_line;
	int		i;
	int		n;

	if (!s2 || !*s2)
		return (0);
	next_line = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!next_line)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		next_line[i] = s1[i];
		i++;
	}
	n = 0;
	while (s2 && s2[n] && s2[n] != '\n')
		next_line[i++] = s2[n++];
	if (s2 && s2[n] == '\n')
		next_line[i++] = '\n';
	next_line[i] = '\0';
	if (s1)
		free(s1);
	return (next_line);
}
