#include "minishell.h"

volatile sig_atomic_t handler = 0;
int main (void)
{
    t_list_token list_token;

    list_token.top = NULL;
    list_token.last = NULL;
   // int g_exit_status = 0; necesario inicializar para manejar el codigo de salida

    init_signals();

    while (1)
    {
        char *line;
        line = readline("MiniShell: > ");
        parser(line, &list_token);
        list_token.top = NULL;
    }
    return 0;
}