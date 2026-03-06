// #include "minishell.h"

// FUNCTIONS

int         count_cmds(t_cmd *cmd);
int         **create_pipes(int n);
void        close_all_pipes(int **pipes, int n);
void        wait_all(int count);
void        execute(t_cmd *cmds, char **envp);
void        execute_pipeline(t_cmd *cmds, char **envp);
void        child_process(t_cmd *cmd, int **pipes, int i, int count, char **envp);
void        apply_redirections(t_cmd *cmd);


int executor(t_shell *sh, t_cmd *cmd_list, char **envp);

void launch_children(t_shell *sh, t_cmd *cmd_list, char **envp, int **pipes, int count);
void wait_and_close(int **pipes, int count, t_shell *sh);

void child_process(t_shell *sh, t_cmd *cmd, int **pipes, int i, int count, char **envp);

int **create_pipes(int count);
void close_all_pipes(int **pipes, int n);

void apply_redirections(t_cmd *cmd);

int exec_builtin(t_shell *sh, t_cmd *cmd);