#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum e_builtin_type
{
    BI_NONE,
    BI_ECHO,
    BI_PWD,
    BI_ENV
} t_builtin_type;

typedef struct s_cmd
{
    char *cmd_name;
    char *args_name;
    char *flag_name;
    char *path;
    int is_att;
    t_builtin_type builtin_type;
} t_cmd;

int g_exit_status = 0;

// ---------- Builtin detection & execution ----------
void detect_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->cmd_name)
        return;

    if (strcmp(cmd->cmd_name, "pwd") == 0)
        cmd->builtin_type = BI_PWD;
    else if (strcmp(cmd->cmd_name, "echo") == 0)
        cmd->builtin_type = BI_ECHO;
    else if (strcmp(cmd->cmd_name, "env") == 0)
        cmd->builtin_type = BI_ENV;
    else
        cmd->builtin_type = BI_NONE;
}

// ---------- Env auxiliary functions ----------
int env_get(char **env, const char *key)
{
    int i = 0;
    size_t key_len = strlen(key);

    while (env && env[i])
    {
        if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

static int env_replace(char **env, int idx, const char *var)
{
    char *new_var;

    new_var = strdup(var);
    if (!new_var)
        return (-1);
    free(env[idx]);
    env[idx] = new_var;
    return (0);
}

static int env_add(char ***env, const char *var)
{
    char    **new_env;
    int     i;

    i = 0;
    while (*env && (*env)[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (-1);
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
        return (-1);
    }
    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
    return (0);
}

int env_set(char ***env, const char *var)
{
    int idx;

    if (!env || !var)
        return (-1);
    idx = env_get(*env, var);
    if (idx != -1)
        return env_replace(*env, idx, var);
    return env_add(env, var);
}


static int count_env(char **env)
{
    int i = 0;

    if (!env)
        return (0);
    while (env[i])
        i++;
    return (i);
}

static int copy_env_skip(char ***env, int idx)
{
    int     i = 0;
    int     j = 0;
    int     size;
    char    **new_env;

    size = count_env(*env);
    new_env = malloc(sizeof(char *) * size);
    if (!new_env)
        return (-1);
    while ((*env)[i])
    {
        if (i != idx)
        {
            new_env[j] = (*env)[i];
            j++;
        }
        else
            free((*env)[i]);
        i++;
    }
    new_env[j] = NULL;
    free(*env);
    *env = new_env;
    return (0);
}

int env_unset(char ***env, const char *key)
{
    int idx;

    if (!env || !key)
        return (-1);
    idx = env_get(*env, key);
    if (idx == -1)
        return (0);
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

// ---------- Builtins ----------
int builtin_env(t_cmd *cmd, char **env)
{
    (void)cmd;
    env_print(env);
    return 0;
}

int builtin_export(t_cmd *cmd, char ***env)
{
    (void)cmd;
    if (!cmd->args_name)
        return 1;
    return env_set(env, cmd->args_name);
}

int builtin_unset(t_cmd *cmd, char ***env)
{
    (void)cmd;
    if (!cmd->args_name)
        return 1;
    return env_unset(env, cmd->args_name);
}

// ---------- Main test ----------
extern char **environ;

int main(void)
{
    // Crear copia del entorno
    int i;
    char **my_env;
    for (i = 0; environ[i]; i++)
        ;
    my_env = malloc(sizeof(char *) * (i + 1));
    for (i = 0; environ[i]; i++)
        my_env[i] = strdup(environ[i]);
    my_env[i] = NULL;

    t_cmd cmd;

    printf("----- ENTORNO ORIGINAL -----\n");
    cmd.cmd_name = "env";
    cmd.args_name = NULL;
    detect_builtin(&cmd);
    builtin_env(&cmd, my_env);

    printf("\n----- EXPORT TEST -----\n");
    cmd.cmd_name = "export";
    cmd.args_name = "TEST_VAR=42";
    detect_builtin(&cmd);
    builtin_export(&cmd, &my_env);
    builtin_env(&cmd, my_env);

    printf("\n----- UNSET TEST -----\n");
    cmd.cmd_name = "unset";
    cmd.args_name = "TEST_VAR";
    detect_builtin(&cmd);
    builtin_unset(&cmd, &my_env);
    builtin_env(&cmd, my_env);

    // Liberar my_env
    for (i = 0; my_env[i]; i++)
        free(my_env[i]);
    free(my_env);

    return 0;
}
