#include "minishell.h"

void	add_cmd_list(t_cmd *new_cmd, t_list_cmd *list_cmd)
{
	new_cmd->next = NULL;
	if (list_cmd->top == NULL)
	{
		list_cmd->top = new_cmd;
		list_cmd->last = new_cmd;
	}
	else
	{
		list_cmd->last->next = new_cmd;
		list_cmd->last = new_cmd;
	}
}

void	create_cmd(t_list_token *s_list_token, t_list_cmd *list_cmd)
{
	while (s_list_token->top != NULL)
	{
		t_cmd	*current_cmd;

		current_cmd = ft_calloc(1, sizeof(t_cmd));
		if (!current_cmd)
			return ;
		current_cmd->heredoc_fd = -1;
		current_cmd->argv = malloc(sizeof(char *)
				* (count_tokes(s_list_token) + 1));
		if (!current_cmd->argv)
		{
			free(current_cmd);
			return ;
		}
		create_cmd_utils(s_list_token, current_cmd);
		detect_builtin(current_cmd);
		add_cmd_list(current_cmd, list_cmd);
	}
}

int	parser(char *line, t_shell *t_shell)
{
	free_token_list(&t_shell->list_token);
	t_shell->list_token.top = NULL;
	t_shell->list_token.last = NULL;
	t_shell->cmd_list.top = NULL;
	t_shell->cmd_list.last = NULL;
	if (line == NULL)
		return (0);
	else
	{
		if (line[0])
			add_history(line);
		if (init_token(line, &t_shell->list_token) == -1)
		{
			t_shell->last_status = 2;
			return (0);
		}
		expand_token_list(&t_shell->list_token, t_shell);
		create_cmd(&t_shell->list_token, &t_shell->cmd_list);
	}
	return (1);
}
