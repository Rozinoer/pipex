#include "pipex.h"

char *get_clean_cmd(char *cmd)
{
    unsigned int i;

    i = 0;
    while (i < ft_strlen(cmd))
    {
        if (*(cmd + i) == ' ')
            break;
        i++;
    }
    return (ft_substr(cmd, 0, i));
}

t_token *new_token()
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
    {
        error("Error: memory not allocate..", 1);
        exit(1);
    }
    return (token);
}

t_token *init_tokens(char **argv)
{
    t_token *token;

    token = new_token();
    token->input_file = argv[1];
    token->output_file = NULL;
    token->execute_cmd = argv[2];
    token->unix_path = NULL;
    token->clean_cmd = get_clean_cmd(token->execute_cmd);
    token->next = new_token();
    token->next->input_file = NULL;
    token->next->output_file = argv[4];
    token->next->execute_cmd = argv[3];
    token->next->unix_path = NULL;
    token->next->clean_cmd = get_clean_cmd(token->next->execute_cmd);
    return (token);
}

int main(int argc, char** argv, char **envp)
{
    t_main pipex;
    t_token *token;

    if (argc != 5)
        return (error("Error: wrong number of argument..", -1));
    token = init_tokens(argv);
    pipex.tokens = token;
    pipex.envp = envp;
    check_argv(token->clean_cmd, token->next->clean_cmd, &pipex);
    execute_cmd(&pipex);
    return 0;
}