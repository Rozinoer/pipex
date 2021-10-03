#ifndef PIPEX_H
#define PIPEX_H

#define TRUE 1
#define FALSE 0

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>

typedef struct s_token
{
    char *output_file;
    char *input_file;
    int output_fd;
    int input_fd;
    char *execute_cmd;
    char *unix_path;
    char *clean_cmd;
    struct s_token	*next;
}   t_token;

typedef struct s_main
{
    char **envp;
    t_token *tokens;
}   t_main;

int error(char *er, int code);
int check_argv(char *c1, char *c2, t_main *pipex);
int execute_cmd(t_main *pipex);

#endif