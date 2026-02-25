#include "minishell.h"

/* Devuelve el valor de la variable de entorno local */
char *get_local_env(const char *key, char **env)
{
    int idx;
    if (!key || !env)
        return NULL;
    idx = env_get(env, key);
    if (idx == -1)
        return NULL;
    return env[idx] + ft_strlen(key) + 1;
}

/* Devuelve valor de variable desde shell */
char *get_var_value(const char *key, t_shell *sh)
{
    return get_local_env(key, sh->env);
}

/* Gestiona el cache de HOME */
char *get_home_cached(t_shell *sh)
{
    char *home = get_var_value("HOME", sh);
    if (!home || home[0] == '\0')
        return sh->cd_home;
    if (!sh->cd_home || ft_strcmp(sh->cd_home, home) != 0)
    {
        free(sh->cd_home);
        sh->cd_home = ft_strdup(home);
        if (!sh->cd_home)
        {
            fprintf(stderr, "minishell: cd: malloc failed\n");
            sh->exit_status = 1;
            return NULL;
        }
    }
    return sh->cd_home;
}

/* Determina si el puntero debe liberarse */
int needs_free(char *arg)
{
    if (!arg)
        return 0;
    return !(ft_strcmp(arg, "-") == 0 || ft_strcmp(arg, "~") == 0);
}

/* Imprime errores de cd de forma consistente */
void print_chdir_error(char *path, char *arg)
{
    fprintf(stderr, "minishell: cd: %s", arg ? arg :
            "HOME");
    if (errno == EACCES)
        fprintf(stderr, ": Permission denied\n");
    else if (errno == ENOTDIR)
        fprintf(stderr, ": Not a directory\n");
    else
        fprintf(stderr, ": No such file or directory\n");
}