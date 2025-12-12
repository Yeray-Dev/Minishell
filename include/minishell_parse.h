#include "minishell.h"

// FUNCTIONS

void init_signals(void);

void handler_sigint(int sig);
void handler_sigquit(int sig);
void handler_readline(int sig);
void set_signal(int sig, void (*handler)(int));

int parser(char *line, t_list_token *list_token);

int init_token(char *line, t_list_token *list_token);
int token_is_quote(char *line, int *i);
int token_is_pipe(char *line, int *i, int *start, t_list_token *list_token);
int token_is_redirect(char *line, int *i, int *start, t_list_token *list_token);
void token_add_list(t_list_token *list_token, char* new_token);