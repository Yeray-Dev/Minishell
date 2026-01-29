#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	builtin_echo(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	print_newline;

	(void)sh;
	i = 1;
	print_newline = 1;
	while (cmd->args_name[i] && is_n_flag(cmd->args_name[i]))
	{
		print_newline = 0;
		i++;
	}
	while (cmd->args_name[i])
	{
		printf("%s", cmd->args_name[i]);
		if (cmd->args_name[i + 1])
			printf(" ");
		i++;
	}
	if (print_newline)
		printf("\n");
	sh->exit_status = 0;
	return (0);
}

