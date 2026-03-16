#include "minishell.h"

static t_exec *prepare_exec(t_shell *sh)
{
    t_cmd *first;
    t_exec *exec;

    first = sh->cmd_list.top;
    if (first && !first->next && first->builtin_type != BI_NONE)
    {
        int save_stdin = dup(STDIN_FILENO);
        int save_stdout = dup(STDOUT_FILENO);
        t_exec_cmd tmp;

        tmp.original = first;

        if (!apply_redirections(&tmp, first))
            exec_builtin(sh, first);

        dup2(save_stdin, STDIN_FILENO);
        dup2(save_stdout, STDOUT_FILENO);

        close(save_stdin);
        close(save_stdout);
        return (NULL);
    }

    exec = init_exec(sh);
    if (!exec)
        return (NULL);

    create_pipes(exec);
    return (exec);
}
void	execute_commands(t_shell *sh)
{
	t_exec	*exec;

	handle_heredocs(&sh->cmd_list);
	exec = prepare_exec(sh);
	if (!exec)
		return ;
	executor_loop(sh, exec);
	close_all_pipes_in_parent(exec);
	wait_children(sh, exec);
	cleanup_exec(exec);
}