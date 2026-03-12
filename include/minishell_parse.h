 #include "minishell.h"

// FUNCTIONS

// Expander -> expander.c
int stract_variables(char *line, int *i, char **our_envp, t_shell *sh);
char **duplicate_envp(char **envp);

// Lexer -> token.c
void token_add_list(t_list_token *list_token, char* new_token);
int init_token(char *line, t_list_token *list_token, char **our_envp);

// Lexer -> token_utils.c
int token_is_quote(char *line, int *i, char **our_envp, t_list_token *list_token);
int token_is_pipe(char *line, int *i, int *start, t_list_token *list_token);
void token_is_double_redirect(char *line, int *i, int *start, t_list_token *list_token);
int token_is_redirect(char *line, int *i, int *start, t_list_token *list_token);

// Parser -> parser.c
void complete_cmd(t_cmd *new_cmd, t_list_cmd *list_cmd, t_tokens **token);
int parser(char *line, t_shell *t_shell);

// Parser -> parser_utils.c
size_t count_tokes(t_list_token *s_list_token);
void free_cmd_list(t_list_cmd *list_cmd);
void set_cmd_link_type(t_cmd *new_cmd, t_tokens **end_token);
void add_cmd_list(t_cmd *new_cmd, t_list_cmd *list_cmd);
void create_cmd(t_list_token *s_list_token, t_list_cmd *list_cmd);

// Signals -> Signal.c
void init_signals(void);

// Signals -> Signal_utils.c
void handler_sigint(int sig);
void handler_sigquit(int sig);
void handler_readline(int sig);
void set_signal(int sig, void (*handler)(int));





