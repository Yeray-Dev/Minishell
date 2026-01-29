#include "minishell.h"

char **env_init(char **envp)
{
    int     i;
    char    **new_env;

    i = 0;
    while (envp && envp[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return (NULL);
    i = 0;
    while (envp && envp[i])
    {
        new_env[i] = ft_strdup(envp[i]);
        if (!new_env[i])
        {
            while (--i >= 0)
                free(new_env[i]);
            free(new_env);
            return (NULL);
        }
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

/*
int main(int argc, char **argv, char **envp)
{
    

    // Copiar el entorno del sistema
    sh.env = env_init(envp);
    if (!sh.env)
    {
        fprintf(stderr, "minishell: failed to initialize environment\n");
        return 1;
    }

    

    // Liberar el entorno al salir
    env_free(sh.env); // función que libera un char ** env
    return 0;
}*/
