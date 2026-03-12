#include "minishell.h"

void complete_cmd(t_cmd *new_cmd, t_list_cmd *list_cmd, t_tokens **token)
{
    set_cmd_link_type(new_cmd, token);
    add_cmd_list(new_cmd, list_cmd);
}

int parser(char *line, t_shell *t_shell)
{
    t_shell->list_token.top = NULL;
    t_shell->list_token.last = NULL;
    t_shell->cmd_list.top = NULL;
    t_shell->cmd_list.last = NULL;
    if (line == NULL)
        return (0);
    else
    {
        add_history(line);
        init_token(line, &t_shell->list_token, t_shell->our_envp);
        create_cmd(&t_shell->list_token, &t_shell->cmd_list);
    }
//     //! TESTING
//     t_cmd *cmd = t_shell->cmd_list.top;
//     int cmd_num = 1;
//     while (cmd)
//     {
//         printf("─── CMD %d ───────────────────\n", cmd_num++);
//         int i = 0;
//         printf("  argv     : ");
//         while (cmd->argv[i])
//             printf("[%s] ", cmd->argv[i++]);
//         printf("\n");
//         printf("  has_pipe : %d\n", cmd->has_pipe);
//         printf("  infile   : %s\n", cmd->infile   ? cmd->infile   : "(none)");
//         printf("  outfile  : %s\n", cmd->outfile  ? cmd->outfile  : "(none)");
//         printf("  append   : %d\n", cmd->append);
//         printf("  is_heredoc   : %d\n", cmd->is_heredoc);
//         printf("  heredoc_word : %s\n", cmd->heredoc_word ? cmd->heredoc_word : "(none)");
//         cmd = cmd->next;
//     }
//     //! END TESTING
    return 1;
}