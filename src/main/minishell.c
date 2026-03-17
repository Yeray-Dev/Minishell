#include "minishell.h"

volatile sig_atomic_t	g_handler = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	t_shell;
	char	*line;

	(void)argc;
	(void)argv;
	init_signals();
	t_shell.our_envp = duplicate_envp(envp);
	t_shell.last_status = 0;
	t_shell.cd_home = NULL;
	t_shell.list_token.shell = &t_shell;
	while (1)
	{
		g_handler = 0;
		line = readline("MiniShell: > ");
		if (line == NULL)
			break ;
		if (g_handler == 1)
		{
			t_shell.last_status = 1;
			g_handler = 0;
			free(line);
			continue ;
		}
		parser(line, &t_shell);
		execute_commands(&t_shell);
		free_cmd_list(&t_shell.cmd_list);
		free(line);
	}
	free_dblptr(t_shell.our_envp);
	return (0);
}
