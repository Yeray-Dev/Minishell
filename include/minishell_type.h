/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_type.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yblanco- <yblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:12:27 by yblanco-          #+#    #+#             */
/*   Updated: 2026/03/18 10:31:59 by yblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ENUM

typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_PIPE,
	TOKEN_REDIRECTIONS
}	t_token_type;

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
}	t_builtin_type;

// DEFINE

#define QUOTES 34
#define QUOTE 39
#define PIPE 124
#define REDIR_OUT 62
#define REDIR_IN 60
#define REDIR_TYPE_IN 0
#define REDIR_TYPE_OUT 1
#define REDIR_TYPE_APPEND 2

// STRUCTS

typedef struct s_redir
{
	char				*file;
	int					type;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char				**argv;
	char				*path;
	t_redir				*redirs;
	char				*heredoc_word;
	int					is_heredoc;
	int					heredoc_fd;
	int					has_pipe;
	t_builtin_type		builtin_type;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_list_cmd
{
	t_cmd				*top;
	t_cmd				*last;
}	t_list_cmd;

typedef struct s_tokens
{
	char				*name;
	int					type;
	int					quotes;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_exec_cmd
{
	char				*path;
	char				**argv;
	int					infile_fd;
	int					outfile_fd;
	int					is_builtin;
	int					builtin_type;
	t_cmd				*original;
	struct s_exec_cmd	*next;
}	t_exec_cmd;

typedef struct s_exec
{
	int					n_cmds;
	int					n_pipes;
	int					**pipes;
	pid_t				*pids;
	t_exec_cmd			*cmds;
}	t_exec;

typedef struct s_list_token
{
	t_tokens			*top;
	t_tokens			*last;
	struct s_shell		*shell;
}	t_list_token;

typedef struct s_shell
{
	t_list_token		list_token;
	t_list_cmd			cmd_list;
	char				**our_envp;
	int					last_status;
	int					exit_status;
	char				*cd_home;
	char				*line;
}	t_shell;

// GLOBALS

extern volatile sig_atomic_t	g_handler;