#include "pipex.h"

int error(char *er, int code)
{
    ft_putstr_fd(er, 1);
    write(1, "\n", 1);
    return (code); 
}