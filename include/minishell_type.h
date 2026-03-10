// #include "minishell.h"

// ENUM

typedef enum e_token_type
{
    TOKEN_CMD,
    TOKEN_PIPE,
    TOKEN_REDIRECTIONS
}token_type;

// DEFINE

#define QUOTES 34
#define QUOTE 39
#define PIPE 124 
#define REDIR_OUT 62
#define REDIR_IN 60


// STRUCTS

typedef struct s_cmd
{
    char **argv; // Cada token
    char *path;
    char *infile; 
    char *outfile;
    char *heredoc_word;
    int is_heredoc; // Definimos si es heredoc. 0 No 1 Si
    int is_builtins; // Definimos si es builtins. 0 No 1 Si
    int append; // \ != 1 si no sobreescribe 1 si sobreescribe
    int has_pipe; 

    struct s_cmd *next;
}t_cmd;

typedef struct s_list_cmd
{
    t_cmd *top;
    t_cmd *last;

} t_list_cmd;

typedef struct s_tokens
{
    char *name;
    int type;
    int quotes;
    struct s_tokens *next;

} t_tokens;

typedef struct s_list_token
{
    t_tokens *top;
    t_tokens *last;

} t_list_token;

typedef struct s_shell
{
    t_list_token list_token;
    t_list_cmd cmd_list;
    char **our_envp;
    int last_status;
    int exit_status;

}t_shell;


// GLOBALS

extern volatile sig_atomic_t handler;