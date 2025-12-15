#include "minishell.h"

// ENUM

typedef enum e_token_type
{
    TOKEN_CMD = 0,
    TOKEN_PIPE = 1,
    TOKEN_REDIRECTIONS = 3
}token_type;

// DEFINE

#define QUOTES 34
#define QUOTE 39
#define PIPE 124 

// STRUCTS

typedef struct s_cmd
{
    char *cmd_name;
    char *args_name;
    char *flag_name;
    char *path;
    int is_att;
    int is_builtins;
}t_cmd;
typedef struct s_tokens
{
    char *name;
    int type;
    int quotes;
    int position;
    struct s_tokens *next;

} t_tokens;

typedef struct s_list_token
{
    t_tokens *top;
    t_tokens *last;
    
} t_list_token;


// GLOBALS

extern volatile sig_atomic_t handler;