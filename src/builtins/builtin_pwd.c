#include "minishell.h"

int builtin_pwd(t_cmd *cmd)
{
    char *cwd;
    (void)cmd;

    cwd = getcwd(NULL, 0);
    if (cwd)
    {
        printf("%s\n", cwd);
        free(cwd);
        return (0);
    }
    else
    {
        perror("pwd");
        return (1);
    }
}
