#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

// Function declarations
void	error(void);
void	error_with_message(const char *message);
void	exe(char *argv, char **envp);
void	ft_error(void);
char	*search_path(char *cmd, char **envp);
void	ft_free(void **ptr);

#endif
