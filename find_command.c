#include "pipex.h"

static char	*search_file(DIR *dir, char *file_path, char *command)
{
	struct dirent	*rd;
	char			*unix_path;
	char			*p;

	unix_path = NULL;
	rd = readdir(dir);
	while (rd != NULL)
	{
		if (ft_strncmp(rd->d_name, command, ft_strlen(rd->d_name)) == 0)
		{
			unix_path = ft_strjoin(file_path, "/");
			p = unix_path;
			unix_path = ft_strjoin(unix_path, command);
			free(p);
			break ;
		}
		rd = readdir(dir);
	}
	closedir(dir);
	return (unix_path);
}

static char	*get_envi_val(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}


static int	free_argv(char **argv, int ret)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(argv[i]);
		i--;
	}
	free(argv);
	argv = NULL;
	return (ret);
}

static int	search_in_path(char *command, t_main *pipex, t_token *token ,int i)
{
	char	*path;
	char	**bin_list;
	DIR		*dir;

	path = get_envi_val(pipex->envp, "PATH");
	if (!path)
		return (0);
	while (*path++ != '=')
		path++;
	bin_list = ft_split(path, ':');
	while (bin_list[i] != NULL)
	{
		dir = opendir(bin_list[i]);
		if (!(dir))
			break ;
		token->unix_path = search_file(dir, bin_list[i], command);
		if (token->unix_path != NULL)
			break ;
		i++;
	}
	if (token->unix_path == NULL)
		return (free_argv(bin_list, 0));
	return (free_argv(bin_list, 1));
}

int check_argv(char *c1, char *c2, t_main *pipex)
{
    if (search_in_path(c1, pipex, pipex->tokens, 0) == 0)
    {
        ft_putstr_fd("Error: command ", 1);
        ft_putstr_fd(c1, 1);
        ft_putstr_fd(" not found..\n", 1);
        exit(1);
    }
    if (search_in_path(c2, pipex, pipex->tokens->next, 0) == 0)
    {
        ft_putstr_fd("Error: command ", 1);
        ft_putstr_fd(c2, 1);
        ft_putstr_fd(" not found..\n", 1);
        exit(1);
    }
    return (0);
}
