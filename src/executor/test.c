#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>      // CAMBIO: para open, O_RDONLY, O_WRONLY, etc.
#include <sys/wait.h>

// ENUMS

typedef enum e_builtin_type
{
    BI_NONE,
    BI_ECHO,
    BI_PWD,
    BI_CD,
    BI_EXPORT,
    BI_UNSET,
    BI_ENV,
    BI_EXIT
} t_builtin_type;

// STRUCTS

typedef struct s_cmd
{
    char **argv; // Cada token
    char *path;
    char *infile; 
    char *outfile;
    int append;
    t_builtin_type builtin_type;
    int has_pipe;
    struct s_cmd *next;
} t_cmd;

typedef struct s_exec_cmd
{
	char	*path;
	char	**argv;
	int		infile_fd;
	int		outfile_fd;
	int		is_builtin;
	int		builtin_type;
	t_cmd	*original;   // <-- aquí guardas el puntero al t_cmd original
	struct s_exec_cmd *next;
} t_exec_cmd;

typedef struct s_exec
{
    int n_cmds;
    int n_pipes;
    int **pipes;
    pid_t *pids;
    t_exec_cmd *cmds;
} t_exec;

typedef struct s_shell
{
    t_cmd *cmd_list_top;
    char **our_envp;
    int last_status;
} t_shell;

// STUBS para builtins (CAMBIO: agregados)
int builtin_echo(t_cmd *cmd)  { printf("ECHO\n"); return 0; }
int builtin_pwd(t_cmd *cmd)   { printf("PWD\n"); return 0; }
int builtin_cd(t_shell *sh, t_cmd *cmd) { printf("CD\n"); return 0; }
int builtin_export(t_shell *sh, t_cmd *cmd) { printf("EXPORT\n"); return 0; }
int builtin_unset(t_shell *sh, t_cmd *cmd) { printf("UNSET\n"); return 0; }
int builtin_env(t_shell *sh, t_cmd *cmd) { printf("ENV\n"); return 0; }
int builtin_exit(t_shell *sh, t_cmd *cmd) { printf("EXIT\n"); return 0; }

// FUNCIONES AUXILIARES

int	count_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

t_exec_cmd	*init_exec_cmd(t_cmd *cmd)
{
	t_exec_cmd	*new;

	new = malloc(sizeof(t_exec_cmd));
	new->argv = cmd->argv;
	new->path = cmd->path;
	new->infile_fd = -1;
	new->outfile_fd = -1;
	new->builtin_type = cmd->builtin_type;
	new->is_builtin = (cmd->builtin_type != BI_NONE);
	new->original = cmd;
	new->next = NULL;
	return (new);
}

t_exec	*init_exec_struct(t_shell *sh, t_cmd *cmd_list)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->n_cmds = count_cmds(cmd_list);
	exec->n_pipes = exec->n_cmds - 1;
	exec->pids = malloc(sizeof(pid_t) * exec->n_cmds);
	exec->pipes = (exec->n_pipes > 0) ? malloc(sizeof(int *) * exec->n_pipes) : NULL;
	exec->cmds = NULL;
	return (exec);
}

void	build_exec_cmd_list(t_exec *exec, t_cmd *cmd_list)
{
	t_exec_cmd	*prev;
	t_exec_cmd	*new;

	prev = NULL;
	while (cmd_list)
	{
		new = init_exec_cmd(cmd_list);
		if (!exec->cmds)
			exec->cmds = new;
		if (prev)
			prev->next = new;
		prev = new;
		cmd_list = cmd_list->next;
	}
}

t_exec	*init_exec(t_shell *sh)
{
	t_exec	*exec;

	exec = init_exec_struct(sh, sh->cmd_list_top);
	build_exec_cmd_list(exec, sh->cmd_list_top);
	return (exec);
}

// CAMBIO: Reemplazado cmd_name por argv[0]
void detect_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->argv || !cmd->argv[0]) return;
    if (strcmp(cmd->argv[0], "pwd") == 0) cmd->builtin_type = BI_PWD;
    else if (strcmp(cmd->argv[0], "echo") == 0) cmd->builtin_type = BI_ECHO;
    else cmd->builtin_type = BI_NONE;
}

int exec_builtin(t_shell *sh, t_cmd *cmd)
{
    int status;
    detect_builtin(cmd);
    if (!cmd || !sh) return 1;
    if (cmd->builtin_type == BI_PWD) status = builtin_pwd(cmd);
    else if (cmd->builtin_type == BI_ECHO) status = builtin_echo(cmd);
    else status = 1;
    sh->last_status = status; // CAMBIO: reemplazado exit_status
    return status;
}

// CAMBIO: funcion temporal para probar single builtin
int execute_single_builtin(t_shell *sh)
{
    t_cmd *first = sh->cmd_list_top;
    if (!first || first->next) return 0;
    if (first->builtin_type != BI_NONE)
    {
        exec_builtin(sh, first);
        return 1;
    }
    return 0;
}

// PIPES
void create_pipes(t_exec *exec)
{
    for (int i = 0; i < exec->n_pipes; i++)
    {
        exec->pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(exec->pipes[i]) < 0) perror("pipe");
    }
}

void close_pipes(t_exec *exec)
{
    if (!exec || !exec->pipes) return;
    for (int i = 0; i < exec->n_pipes; i++)
    {
        close(exec->pipes[i][0]);
        close(exec->pipes[i][1]);
    }
}

void setup_pipes(t_exec *exec, int i)
{
    // Si no es el primer comando, conecta stdin al pipe anterior
    if (i != 0)
    {
        dup2(exec->pipes[i - 1][0], STDIN_FILENO);
        close(exec->pipes[i - 1][0]);
        close(exec->pipes[i - 1][1]);
    }

    // Si no es el último comando, conecta stdout al pipe actual
    if (i != exec->n_cmds - 1)
    {
        dup2(exec->pipes[i][1], STDOUT_FILENO);
        close(exec->pipes[i][0]);
        close(exec->pipes[i][1]);
    }
}
//done

void	exec_child(t_shell *sh, t_exec_cmd *cmd, int i, t_exec *exec)
{
	setup_pipes(exec, i);

	if (cmd->is_builtin)
	{
		exec_builtin(sh, cmd->original); // usamos t_cmd original desde cmd->original
		exit(sh->last_status);
	}

	execve(cmd->path, cmd->argv, sh->our_envp);
	perror(cmd->argv[0]);
	exit(127);
}
//done
void	executor_loop(t_shell *sh, t_exec *exec)
{
	t_exec_cmd	*cmd;
	int			i;

	cmd = exec->cmds;
	i = 0;
	while (cmd)
	{
		exec->pids[i] = fork();
		if (exec->pids[i] < 0)
			perror("fork");
		else if (exec->pids[i] == 0)
			exec_child(sh, cmd, i, exec); // <-- solo 4 argumentos
		cmd = cmd->next;
		i++;
	}
}

void close_all_pipes_in_parent(t_exec *exec)
{
    if (!exec || !exec->pipes)
        return;
    for (int i = 0; i < exec->n_pipes; i++)
    {
        close(exec->pipes[i][0]);
        close(exec->pipes[i][1]);
    }
}

void wait_children(t_shell *sh, t_exec *exec)
{
    for (int i = 0; i < exec->n_cmds; i++)
    {
        int status;
        waitpid(exec->pids[i], &status, 0);
        if (WIFEXITED(status)) sh->last_status = WEXITSTATUS(status);
    }
}

void free_exec_resources(t_exec *exec)
{
    for (int i = 0; i < exec->n_pipes; i++) free(exec->pipes[i]);
    free(exec->pipes);
    free(exec->pids);
    t_exec_cmd *cmd = exec->cmds;
    while (cmd) { t_exec_cmd *tmp = cmd->next; free(cmd); cmd = tmp; }
    free(exec);
}

void execute_commands(t_shell *sh)
{
    if (execute_single_builtin(sh)) return; // CAMBIO: reemplazado exec_builtin(sh)
    t_exec *exec = init_exec(sh);
    create_pipes(exec);
    executor_loop(sh, exec);

    // CAMBIO: cerrar todos los pipes en el padre antes de esperar hijos
    close_all_pipes_in_parent(exec);

    wait_children(sh, exec);
    free_exec_resources(exec);
}

// FUNCION PRINCIPAL
int main(void)
{
    t_shell sh;
    sh.our_envp = NULL;
    sh.last_status = 0;

    t_cmd cmd1, cmd2, cmd3;

    cmd1.argv = malloc(sizeof(char*) * 2);
    cmd1.argv[0] = strdup("echo");
    cmd1.argv[1] = NULL;
    cmd1.path = NULL;
    cmd1.builtin_type = BI_NONE;
    cmd1.next = &cmd2;

    cmd2.argv = malloc(sizeof(char*) * 2);
    cmd2.argv[0] = strdup("pwd");
    cmd2.argv[1] = NULL;
    cmd2.path = NULL;
    cmd2.builtin_type = BI_NONE;
    cmd2.next = &cmd3;

    cmd3.argv = malloc(sizeof(char*) * 2);
    cmd3.argv[0] = strdup("env");
    cmd3.argv[1] = NULL;
    cmd3.path = NULL;
    cmd3.builtin_type = BI_NONE;
    cmd3.next = NULL;

    sh.cmd_list_top = &cmd1;

    execute_commands(&sh);

    free(cmd1.argv[0]); free(cmd1.argv);
    free(cmd2.argv[0]); free(cmd2.argv);
    free(cmd3.argv[0]); free(cmd3.argv);

    return 0;
}