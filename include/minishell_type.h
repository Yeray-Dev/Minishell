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
    t_builtin_type builtin_type; // Definimos si es builtins. 0 No 1 Si
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

typedef struct s_exec_cmd
{
	char	*path;
	char	**argv;
	int		infile_fd;
	int		outfile_fd;
	int		is_builtin;
	int		builtin_type;
	t_cmd	*original;   // <-- aquí guardas el puntero al t_cmd original
	struct s_exec_cmd *next;
} t_exec_cmd;

typedef struct s_exec
{
    int n_cmds;
    int n_pipes;

    int **pipes;
    pid_t *pids;

    t_exec_cmd *cmds;

} t_exec;

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
    char *cd_home;

}t_shell;


// GLOBALS

extern volatile sig_atomic_t handler;
extern int g_status;