#include "pipex.h"

static int check_fd(t_main *pipex)
{
    if (access(pipex->tokens->input_file, 0) == -1)
        exit(error("Error: input file not available..", 1));
    else if (access(pipex->tokens->input_file, 4) == -1)
        exit(error("Error: input file not available to read..", 1));
    else
        pipex->tokens->input_fd = open(pipex->tokens->input_file, O_RDONLY, 0);
    if (access(pipex->tokens->next->output_file, 0) == 0)
    {
        if (!(access(pipex->tokens->next->output_file, 2) == 0
        || access(pipex->tokens->next->output_file, 4) == 0))
            exit(error("Error: output file not available to write..", 1));
        pipex->tokens->next->output_fd = open(pipex->tokens->next->output_file,
        O_WRONLY | O_TRUNC);
    }
    else
        pipex->tokens->next->output_fd = open(pipex->tokens->next->output_file,
        O_CREAT | O_RDWR | O_TRUNC, S_IREAD|S_IWRITE);
    printf("output fd: %d\n", pipex->tokens->next->output_fd);
    return (0);
}

static int set_fd(t_main *pipex)
{
    return (check_fd(pipex));
}

int execute_cmd(t_main *pipex)
{
    int pid;
    int fd[2];

    set_fd(pipex);
    if (pipe(fd) == -1)
        exit(error("Error: pipe not create..", 1));
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        dup2(pipex->tokens->input_fd, 0);
        execve(pipex->tokens->unix_path, ft_split(pipex->tokens->execute_cmd, ' '),pipex->envp);
    }
    else
    {
    wait(NULL);
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        dup2(pipex->tokens->next->output_fd, 1);
        execve(pipex->tokens->next->unix_path,
        ft_split(pipex->tokens->next->execute_cmd, ' '),pipex->envp);
    }
    return (0);
}