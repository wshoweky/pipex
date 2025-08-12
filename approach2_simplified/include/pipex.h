#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

/* Function prototypes */
void	ft_free(char **ptr);
void	error_with_message(const char *msg);
void	exe(char *argv, char **envp);
void	process_heredoc(char *limiter);
void	process_command(char *cmd, char **envp, int *process_count);
void	wait_for_all_processes(int count);
void	show_usage(void);
char	*search_path(char *cmd, char **envp);

/* String utilities */
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

#endif
