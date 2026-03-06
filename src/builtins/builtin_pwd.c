int	builtin_pwd(t_shell *sh, t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		sh->exit_status = 0;
	}
	else if (sh->pwd)
	{
		printf("%s\n", sh->pwd);
		sh->exit_status = 0;
	}
	else
	{
		printf("minishell: pwd: error retrieving current directory\n");
		sh->exit_status = 1;
	}
	return (sh->exit_status);
}