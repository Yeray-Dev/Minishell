#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// ---------- DETECTAR Y EJECUTAR BUILTINS ----------
void    detect_builtin(t_cmd *cmd);
int exec_builtin(t_shell *sh, t_cmd *cmd)


// ---------- BUILTINS ----------
int builtin_pwd(t_cmd *cmd);
int builtin_echo(t_cmd *cmd);
int builtin_env(t_shell *sh, t_cmd *cmd);
int builtin_export(t_shell *sh, t_cmd *cmd);
int builtin_unset(t_shell *sh, t_cmd *cmd);



// ---------- FUNCIONES AUXILIARES DE ENTORNO ----------
char    **env_init(char **envp);       // Inicializa copia del entorno
void    env_print(char **env);         // Imprime todas las variables
int env_get(char **env, const char *key);     // Obtiene índice de variable
int env_set(char ***env, const char *var);   // Añade o actualiza variable
int env_unset(char ***env, const char *key); // Elimina variable

#endif
