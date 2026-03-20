/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:12:38 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/19 08:43:42 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FUNCTIONS

// Expander -> expander.c
char		**duplicate_envp(char **envp);
void		expand_token_list(t_list_token *list_token, t_shell *sh);
char		*expand_var(char *raw, int *i, t_shell *sh);

// Expander -> expander_utils.c
char		*str_join_free(char *s1, char *s2);
char		*str_append_char(char *s, char c);

// Expander -> expander_quotes.c
char		*expand_in_double(char *raw, int *i, t_shell *sh);
char		*expand_in_single(char *raw, int *i);
int			has_quotes(char *s);

// Token -> token.c
void		token_add_list(t_list_token *list_token, char *new_token);
int			init_token(t_list_token *list_token);
t_tokens	*remove_token(t_list_token *list, t_tokens *prev, t_tokens *tok);

// Token -> token_utils.c
int			token_is_quote(char *line, int *i);
int			token_is_pipe(char *line, int *i, int *start,
				t_list_token *list_token);
void		token_is_double_redirect(char *line, int *i, int *start,
				t_list_token *list_token);
int			token_is_redirect(char *line, int *i, int *start,
				t_list_token *list_token);
void		free_token_list(t_list_token *list_token);

// Token -> token_stract.c
int			*special_token(char *line, t_list_token *lst, int *i);

// Parser -> parser.c
void		create_cmd(t_list_token *s_list_token, t_list_cmd *list_cmd);
int			parser(t_shell *t_shell);

// Parser -> parser_free.c
void		free_redirs(t_redir *redir);
void		free_cmd_list(t_list_cmd *list_cmd);

// Parser -> parser_utils.c
size_t		count_tokes(t_list_token *s_list_token);
void		set_cmd_link_type(t_cmd *new_cmd, t_tokens **end_token);
void		add_cmd_list(t_cmd *new_cmd, t_list_cmd *list_cmd);
void		create_cmd_utils(t_list_token *s_list_token, t_cmd *current_cmd);

// Signals -> signals_main_utils.c
int			signal_proccess(t_shell *sh);

// Signals -> Signal.c
void		init_signals(void);

// Signals -> Signal_utils.c
void		handler_sigint(int sig);
void		handler_sigquit(int sig);
void		handler_readline(int sig);
void		handler_heredoc(int sig);
void		set_signal(int sig, void (*handler)(int));
