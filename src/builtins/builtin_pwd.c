#include "minishell.h"

int builtin_pwd(t_shell *sh, t_cmd *cmd)
{
    char *cwd;

    (void)cmd;
    cwd = getcwd(NULL, 0);
    if (cwd != NULL)
    {
        printf("%s\n", cwd);
        free(cwd);
        sh->exit_status = 0;
    }
    else
    {
        perror("pwd");
        sh->exit_status = 1;
    }
    return (sh->exit_status);
}
