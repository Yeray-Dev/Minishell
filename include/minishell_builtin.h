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
void builtin_exit(t_shell *sh, t_cmd *cmd);

// ---------- AUXILIARS ------------
void free_dblptr(char **ptr);
static char *ft_strjoin3(const char *a, const char *b, const char *c);
long long atoi_overflow(const char *str, int *error);
// ---------- FUNCIONES AUXILIARES DE ENTORNO ----------
char **copy_env(char **env);
int apply_temp_vars(char **tokens, int end, char ***envp);
void fork_and_exec(char **tokens, char **envp, int *exit_status);
void fork_and_exec(char **tokens, char **envp, int *exit_status);

// ---------- FUNCIONES EXPORT --------
static void export_one(t_shell *sh, char *arg, int *has_error);
static void print_export(char *var);
static void env_sort(char **env);
static char **env_copy(char **env);

// ------------ FUNCIONES CD ---------
char *get_local_env(const char *key, char **env);
char *get_var_value(const char *key, t_shell *sh);
int needs_free(char *arg);
void	print_chdir_error(char *path, char *arg);
char	*update_home_cache(t_shell *sh, char *current);
char	*handle_oldpwd_dir(t_shell *sh);
char	*handle_home_dir(t_shell *sh);
char	*get_new_pwd(char *oldpwd, char *path, char *arg);
void update_environment(t_shell *sh, char *oldpwd, char *pwd);
int change_directory(t_shell *sh, char *path, char *arg);
char *get_target_path(t_shell *sh, char *arg);

#endif
