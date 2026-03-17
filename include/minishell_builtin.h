/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:12:32 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/17 19:12:32 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

# include "minishell.h"
//cambiar exit status en todos por last status
// ---------- DETECTAR Y EJECUTAR BUILTINS ----------
void		detect_builtin(t_cmd *cmd);
int			exec_builtin(t_shell *sh, t_cmd *cmd);

// ---------- BUILTINS ----------
int			builtin_pwd(t_shell *sh, t_cmd *cmd);
int			builtin_echo(t_shell *sh, t_cmd *cmd);
int			builtin_env(t_shell *sh, t_cmd *cmd);
int			builtin_export(t_shell *sh, t_cmd *cmd);
int			builtin_unset(t_shell *sh, t_cmd *cmd);
void		builtin_exit(t_shell *sh, t_cmd *cmd);
int			builtin_cd(t_shell *sh, t_cmd *cmd);

// ---------- AUXILIARES GENERALES ------------
void		free_dblptr(char **ptr);
char		*ft_strjoin3(const char *a, const char *b, const char *c);
long long	atoi_overflow(const char *str, int *error);
char		*ft_substr(const char *s, unsigned int start, size_t len);

// ---------- FUNCIONES AUXILIARES DE ENTORNO ----------
/* env_init_utils.c */
char		**copy_env(char **env);
char		**env_init(char **envp);
int			apply_temp_vars(char **tokens, int end, char ***envp);

/* env_get_set.c */
int			env_get(char **env, const char *key);
int			env_set(char ***env, const char *var);
int			env_add_empty(char ***env, const char *name);

/* env_path_exec.c */
char		*get_command_path(char *cmd, char **envp);
void		fork_and_exec(char **tokens, char **envp, int *exit_status);

// ---------- FUNCIONES EXPORT ----------
void		export_one(t_shell *sh, char *arg, int *has_error);
void		print_export(char *var);
void		env_sort(char **env);
char		**env_copy(char **env);
int			is_valid_identifier(const char *str);
char		*get_var_name(const char *arg);

// ---------- FUNCIONES CD ----------
/* cd_utils.c */
char		*get_local_env(const char *key, char **env);
char		*get_var_value(const char *key, t_shell *sh);
char		*get_home_cached(t_shell *sh);
int			needs_free(char *arg);
void		print_chdir_error(char *path, char *arg);

/* cd_path.c */
char		*get_parent_from_pwd(t_shell *sh);
char		*build_path_component(char *base, char *component);
char		*calculate_logical_pwd(char *current, char *path);
char		*get_new_pwd(char *oldpwd, char *path, char *arg);

/* cd_target.c */
char		*get_target_path(t_shell *sh, char *arg);
int			change_directory(t_shell *sh, char *path, char *arg);
void		update_environment(t_shell *sh, char *oldpwd, char *pwd);

#endif
