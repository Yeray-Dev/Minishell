#include "minishell.h"

void detect_builtin(t_cmd *cmd);
int exec_builtin(t_cmd *cmd);

// builtins

int builtin_pwd(t_cmd *cmd);
int builtin_echo(t_cmd *cmd);
