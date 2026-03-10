
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


volatile sig_atomic_t handler;

void handler_sigint(int sig)
{
    (void)sig;
    handler = 2;
}
void handler_sigquit(int sig)
{
    (void)sig;
    handler = 3;
}
void handler_readline(int sig)
{
    (void)sig;
    write(1, "\n",1 );
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
void set_signal(int sig, void (*handler)(int))
{
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    sigaction(sig, &sa, NULL);
}
int main(){
    while (1){
        handler = 0;

        set_signal(SIGINT, handler_readline);
        set_signal(SIGQUIT, SIG_IGN);

        char *line = readline("Promt > ");
        


        if (line == NULL){ // Gestiona CTRL + D -> CIERRA LA BASH
            printf("\n");
            break;
        }

        

        if (strlen(line) > 0)
            add_history(line);
        
        if (strcmp(line, "EJECUTA") == 0){
            signal(SIGINT, handler_sigint);
            signal(SIGQUIT, handler_sigquit);
            while(1){
                if (handler == 2) // GESTIONA CTRL + C, JUNTO A LA FUNCION handler_function, Y TERMINA EL PROCESO PERO NO CIERRA LA BASH.
                {
                    free(line);
                    handler = 0;
                    break;
                }
                else if (handler == 3) // GESTIONA CTRL + \ , JUNTO A LA FUNCION handler_function, TERMINA EL PROCESO Y MUESTRA CORE DUP PERO NO CIERRA LA BASH.
                {
                    write(1, "CORE DUP\n", 9);
                    free(line);
                    handler = 0;
                    break;
                }
                printf("HOla\n");
            }
            // free(line);
        }
    }
    return 0;
}