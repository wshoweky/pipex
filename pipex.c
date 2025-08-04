#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

void	sub_process(int *pipe_fd, char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0644);
	if (-1 == infile)
		error();	
	dup2 (infile, STDIN_FILENO);
	dup2 (pipe_fd[1], STDOUT_FILENO);
	close (infile);
	close (pipe_fd[1]);
	close (pipe_fd[0]);
	exe (argv[2], envp);
}

void	original_process(int *pipe_fd, char **argv, char **envp)
{
	int	outfile;

	outfile = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (-1 == outfile)
		error ();	
	dup2 (outfile, STDOUT_FILENO);
	dup2 (pipe_fd[0], STDIN_FILENO);
	close (outfile);
	close (pipe_fd[0]);	
	close (pipe_fd[1]);
	exe (argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
    int pipe_fd[2];
    pid_t pid;

    if (5 == argc)
    {
        if (-1 == pipe(pipe_fd))
          error();
        pid = fork();
        if (-1 == pid)
            error();
        if (0 == pid)
            sub_process(pipe_fd, argv, envp);
        waitpid(pid, NULL, 0);
        original_process(pipe_fd, argv, envp);
    }
    else
	    perror(strerror(22));
    return (1);
}
