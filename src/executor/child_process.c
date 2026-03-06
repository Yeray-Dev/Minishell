#include "minishell.h"


/*
Configura stdin y stdout del proceso hijo
según su posición dentro del pipeline.
*/
static void setup_pipes(int **pipes, int i, int count)
{
    if (i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (i < count - 1)
        dup2(pipes[i][1], STDOUT_FILENO);
    close_all_pipes(pipes, count - 1);
}

/*
Código que ejecuta cada proceso hijo:
aplica redirecciones, ejecuta builtin o execve.
*/
void child_process(t_shell *sh, t_cmd *cmd, int **pipes, int i, int count, char **envp)
{
    setup_pipes(pipes, i, count);
    apply_redirections(cmd);
    if (cmd->builtin_type != BI_NONE)
        exit(exec_builtin(sh, cmd));
    if (!cmd->path)
    {
        perror("command not found");
        exit(127);
    }
    execve(cmd->path, cmd->argv, envp);
    perror("execve");
    exit(126);
}