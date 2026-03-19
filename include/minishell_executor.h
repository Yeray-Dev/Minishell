/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:12:35 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/17 19:12:35 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FUNCTIONS
/*
** EXECUTOR INITIALIZATION
*/
int			count_cmds(t_cmd *cmd);
t_exec_cmd	*init_exec_cmd(t_cmd *cmd);
t_exec		*init_exec_struct(t_cmd *cmd_list);
void		build_exec_cmd_list(t_exec *exec, t_cmd *cmd_list);
t_exec		*init_exec(t_shell *sh);

/*
** PIPES
*/
void		create_pipes(t_exec *exec);
void		close_pipes(t_exec *exec);
void		setup_pipes(t_exec *exec, int i);
void		close_all_pipes_in_parent(t_exec *exec);

/*
** EXECUTOR LOOP
*/
void		exec_child(t_shell *sh, t_exec_cmd *cmd, int i, t_exec *exec);
void		executor_loop(t_shell *sh, t_exec *exec);

/*
** WAIT & CLEANUP
*/
void		wait_children(t_shell *sh, t_exec *exec);
void		free_exec_resources(t_exec *exec);

/*
** EXECUTION
*/
void		execute_commands(t_shell *sh);
void		cleanup_exec(t_exec *exec);
/*
** PATH
*/

char		*resolve_path(char *cmd, char **env);

/*
** REDIRECTIONS
*/
void		handle_heredocs(t_list_cmd *cmd_list);
int			apply_redirections(t_exec_cmd *cmd, t_cmd *original);
int			apply_redirections_utils(int last_out_failed,
				t_redir *current_redir);