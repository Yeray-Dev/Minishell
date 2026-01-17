#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ---------------- ENUMS ----------------
typedef enum e_builtin_type
{
    BI_NONE,
    BI_ENV,
    BI_EXPORT,
    BI_UNSET
} t_builtin_type;

// ---------------- STRUCTS ----------------
typedef struct s_cmd
{
    char *cmd_name;
    char *args_name;
    int is_att;
    t_builtin_type builtin_type;
} t_cmd;

typedef struct s_shell
{
    char **env;
    int exit_status;
} t_shell;

// ---------------- AUX FUNCTIONS ----------------
int env_get(char **env, const char *key)
{
    int i = 0;
    size_t key_len = strlen(key);

    while (env && env[i])
    {
        if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return i;
        i++;
    }
    return -1;
}

static int env_replace(char **env, int idx, const char *var)
{
    char *new_var = strdup(var);
    if (!new_var)
        return -1;
    free(env[idx]);
    env[idx] = new_var;
    return 0;
}

static int env_add(char ***env, const char *var)
{
    int i = 0;
    while (*env && (*env)[i])
        i++;

    char **new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return -1;

    i = 0;
    while (*env && (*env)[i])
    {
        new_env[i] = (*env)[i];
        i++;
    }

    new_env[i] = strdup(var);
    if (!new_env[i])
    {
        free(new_env);
        return -1;
    }

    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
    return 0;
}

int env_set(char ***env, const char *var)
{
    int idx = env_get(*env, var);
    if (idx != -1)
        return env_replace(*env, idx, var);
    return env_add(env, var);
}

static int count_env(char **env)
{
    int i = 0;
    if (!env)
        return 0;
    while (env[i])
        i++;
    return i;
}

static int copy_env_skip(char ***env, int idx)
{
    int i = 0, j = 0;
    int size = count_env(*env);
    char **new_env = malloc(sizeof(char *) * size);
    if (!new_env)
        return -1;

    while ((*env)[i])
    {
        if (i != idx)
        {
            new_env[j++] = (*env)[i];
        }
        else
            free((*env)[i]);
        i++;
    }
    new_env[j] = NULL;
    free(*env);
    *env = new_env;
    return 0;
}

int env_unset(char ***env, const char *key)
{
    if (!env || !key)
        return -1;
    int idx = env_get(*env, key);
    if (idx == -1)
        return 0;
    return copy_env_skip(env, idx);
}

void env_print(char **env)
{
    int i = 0;
    while (env && env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

char **env_init(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;

    char **new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return NULL;

    i = 0;
    while (envp[i])
    {
        new_env[i] = strdup(envp[i]);
        if (!new_env[i])
        {
            while (--i >= 0)
                free(new_env[i]);
            free(new_env);
            return NULL;
        }
        i++;
    }
    new_env[i] = NULL;
    return new_env;
}

// ---------------- BUILTINS ----------------
int builtin_env(t_shell *sh, t_cmd *cmd)
{
    (void)cmd;
    env_print(sh->env);
    return 0;
}

int builtin_export(t_shell *sh, t_cmd *cmd)
{
    if (!cmd->args_name)
        return 1;
    return env_set(&sh->env, cmd->args_name);
}

int builtin_unset(t_shell *sh, t_cmd *cmd)
{
    if (!cmd->args_name)
        return 1;
    return env_unset(&sh->env, cmd->args_name);
}

// ---------------- DETECT & EXEC ----------------
void detect_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->cmd_name)
        return;

    if (strcmp(cmd->cmd_name, "env") == 0)
        cmd->builtin_type = BI_ENV;
    else if (strcmp(cmd->cmd_name, "export") == 0)
        cmd->builtin_type = BI_EXPORT;
    else if (strcmp(cmd->cmd_name, "unset") == 0)
        cmd->builtin_type = BI_UNSET;
    else
        cmd->builtin_type = BI_NONE;
}

int exec_builtin(t_shell *sh, t_cmd *cmd)
{
    int status = 1;
    if (!sh || !cmd)
        return status;

    if (cmd->builtin_type == BI_ENV)
        status = builtin_env(sh, cmd);
    else if (cmd->builtin_type == BI_EXPORT)
        status = builtin_export(sh, cmd);
    else if (cmd->builtin_type == BI_UNSET)
        status = builtin_unset(sh, cmd);

    sh->exit_status = status;
    return status;
}

// ---------------- MAIN TEST ----------------
extern char **environ;

int main(void)
{
    t_shell sh;
    sh.env = env_init(environ);
    sh.exit_status = 0;

    t_cmd cmd;

    printf("----- ENTORNO ORIGINAL -----\n");
    cmd.cmd_name = "env";
    cmd.args_name = NULL;
    detect_builtin(&cmd);
    exec_builtin(&sh, &cmd);

    printf("\n----- EXPORT TEST -----\n");
    cmd.cmd_name = "export";
    cmd.args_name = "TEST_VAR=42";
    detect_builtin(&cmd);
    exec_builtin(&sh, &cmd);

    cmd.cmd_name = "env";
    cmd.args_name = NULL;
    detect_builtin(&cmd);
    exec_builtin(&sh, &cmd);

    printf("\n----- UNSET TEST -----\n");
    cmd.cmd_name = "unset";
    cmd.args_name = "TEST_VAR";
    detect_builtin(&cmd);
    exec_builtin(&sh, &cmd);

    cmd.cmd_name = "env";
    cmd.args_name = NULL;
    detect_builtin(&cmd);
    exec_builtin(&sh, &cmd);

    // Liberar entorno
    for (int i = 0; sh.env[i]; i++)
        free(sh.env[i]);
    free(sh.env);

    return 0;
}
