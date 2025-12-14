#include "minishell.h"

// ENUM

typedef enum e_token_type
{
    TOKEN_CMD,
    TOKEN_PIPE,
    TOKEN_REDIRECTIONS
}token_type;

typedef enum e_builtin_type
{
    BI_NONE,
    BI_ECHO,
    BI_PWD,
    BI_CD,
    BI_EXPORT,
    BI_UNSET,
    BI_ENV,
    BI_EXIT
} t_builtin_type;

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
    t_builtin_type builtin_type;
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
extern int g_exit_status;