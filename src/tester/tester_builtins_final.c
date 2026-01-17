#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

/* --- ENUM Y STRUCTS --- */
typedef enum e_builtin_type { BI_NONE, BI_ECHO, BI_PWD, BI_CD, BI_EXPORT, BI_UNSET, BI_ENV, BI_EXIT } t_builtin_type;

typedef struct s_shell { char **env; int exit_status; } t_shell;
typedef struct s_cmd { char *cmd_name; char **args_name; char *flag_name; char *path; int is_att; t_builtin_type builtin_type; } t_cmd;

/* --- ENTORNO --- */
char **env_init(char **envp) { int i=0; while(envp&&envp[i]) i++; char **new_env=malloc(sizeof(char*)*(i+1)); if(!new_env) return NULL; i=0; while(envp&&envp[i]){ new_env[i]=strdup(envp[i]); if(!new_env[i]){while(--i>=0)free(new_env[i]);free(new_env);return NULL;} i++; } new_env[i]=NULL; return new_env;}
int env_get(char **env,const char *key){ int i=0; size_t len;if(!env||!key) return -1; len=strlen(key); while(env[i]){if(strncmp(env[i],key,len)==0&&env[i][len]=='=') return i; i++;} return -1;}
int env_set(char ***env,const char *var){ int idx=env_get(*env,var),i=0; char **new_env; if(!env||!var) return -1; if(idx!=-1){free((*env)[idx]); (*env)[idx]=strdup(var); return 0;} while(*env&&(*env)[i]) i++; new_env=malloc(sizeof(char*)*(i+2)); if(!new_env) return -1; i=0; while(*env&&(*env)[i]){new_env[i]=(*env)[i]; i++;} new_env[i]=strdup(var); new_env[i+1]=NULL; free(*env); *env=new_env; return 0;}
int env_unset(char ***env,const char *key){ int idx,i,j,size; char **new_env; if(!env||!key) return -1; idx=env_get(*env,key); if(idx==-1) return 0; for(size=0;(*env)[size];size++); new_env=malloc(sizeof(char*)*size); if(!new_env) return -1; i=0;j=0; while((*env)[i]){if(i!=idx) new_env[j++]=(*env)[i]; else free((*env)[i]); i++;} new_env[j]=NULL; free(*env); *env=new_env; return 0;}
void print_env(char **env){ int i=0; if(!env){printf("(null)\n"); return;} while(env[i]){printf("%s\n",env[i]); i++;}}

/* --- BUILTINS --- */
static int is_valid_identifier(const char *s){ int i; if(!s||(!isalpha(s[0])&&s[0]!='_')) return 0; i=1; while(s[i]&&s[i]!='='){if(!isalnum(s[i])&&s[i]!='_') return 0;i++;} return 1;}
static void export_arg(t_shell *sh,const char *arg){int res;if(!is_valid_identifier(arg)){sh->exit_status=1; return;} res=env_set(&sh->env,arg); if(res!=0) sh->exit_status=1;}
int builtin_export(t_shell *sh,t_cmd *cmd){int i; if(!sh||!cmd||!cmd->args_name){if(sh){sh->exit_status=1; return(sh->exit_status);} return 1;} sh->exit_status=0;i=0; while(cmd->args_name[i]){export_arg(sh,cmd->args_name[i]);i++;} return sh->exit_status;}
static void unset_arg(t_shell *sh,const char *arg){int res = env_unset(&sh->env,arg); if(res!=0) sh->exit_status=1;}
int builtin_unset(t_shell *sh,t_cmd *cmd){int i; if(!sh||!sh->env||!cmd||!cmd->args_name){if(sh){sh->exit_status=1; return(sh->exit_status);} return 1;} sh->exit_status=0;i=0; while(cmd->args_name[i]){unset_arg(sh,cmd->args_name[i]); i++;} return sh->exit_status;}
int builtin_env(t_shell *sh,t_cmd *cmd){(void)cmd;if(!sh||!sh->env){if(sh){sh->exit_status=1; return(sh->exit_status);} return 1;} sh->exit_status=0; print_env(sh->env); return sh->exit_status;}
static void echo_print_arg(t_shell *sh,char *arg){if(!arg) return; if(strcmp(arg,"$?")==0){if(sh) printf("%d",sh->exit_status); else printf("0");}else printf("%s",arg);}
static void echo_print_args(t_shell *sh,char **args){int i=0; while(args&&args[i]){echo_print_arg(sh,args[i]); if(args[i+1]) printf(" "); i++;}}
static int echo_has_n_flag(char **args){if(!args) return 0; if(strcmp(args[0],"-n")==0) return 1; return 0;}
int builtin_echo(t_shell *sh,t_cmd *cmd){int print_newline; char **args; if(!cmd){if(sh){sh->exit_status=1; return(sh->exit_status);} return 1;} args=cmd->args_name; print_newline=1; if(echo_has_n_flag(args)){print_newline=0; args++;} echo_print_args(sh,args); if(print_newline) printf("\n"); if(sh) sh->exit_status=0; return sh->exit_status;}
int builtin_pwd(t_shell *sh,t_cmd *cmd){(void)cmd; char cwd[PATH_MAX]; if(getcwd(cwd,sizeof(cwd))){printf("%s\n",cwd); if(sh) sh->exit_status=0;} else{perror("pwd"); if(sh) sh->exit_status=1;} return sh?sh->exit_status:0;}

/* --- CAPTURA STDOUT --- */
char *capture_output(int (*func)(t_shell*, t_cmd*), t_shell *sh, t_cmd *cmd)
{
    char *buffer=malloc(8192); buffer[0]='\0';
    FILE *old=stdout;
    FILE *pipe=tmpfile();
    if(!pipe) return NULL;
    fflush(stdout);
    stdout=pipe;
    func(sh,cmd);
    fflush(stdout);
    fseek(pipe,0,SEEK_SET);
    size_t n=fread(buffer,1,8191,pipe);
    buffer[n]='\0';
    stdout=old;
    fclose(pipe);
    return buffer;
}

/* --- COMPARAR ENTORNO --- */
int compare_env(char **env, char **expected){ int i=0; while(env[i]&&expected[i]){if(strcmp(env[i],expected[i])!=0) return 0; i++;} if(env[i]!=NULL||expected[i]!=NULL) return 0; return 1;}

/* --- TEST SUITE --- */
typedef struct s_test_result{ int total; int passed; } t_test_result;
t_test_result test_res={0,0};

void test_builtin(t_shell *sh,t_cmd *cmd,int (*func)(t_shell*, t_cmd*),
                  const char *expected_output,int expected_status,const char *name)
{
    char *out=capture_output(func,sh,cmd);
    int passed = (strcmp(out,expected_output)==0 && sh->exit_status==expected_status);
    test_res.total++;
    if(passed) test_res.passed++;
    printf("TEST %-20s\nEXPECTED OUTPUT:\n%s\nACTUAL OUTPUT:\n%s\nEXPECTED STATUS:%d | ACTUAL STATUS:%d | %s\n\n",
           name,expected_output,out,expected_status,sh->exit_status,passed?"SUCCESS":"FAIL");
    free(out);
}

/* --- MAIN DEFINITIVO --- */
int main(void)
{
    t_shell sh;
    char *base_env[]={"USER=guest","PATH=/usr/bin",NULL};
    sh.env=env_init(base_env);

    printf("=== ULTRA TEST SUITE TODOS BUILTINS ===\n\n");

    /* EXPORT */
    char *exp1[]={"EDITOR=vim","LANG=en_US.UTF-8",NULL};
    t_cmd cmd_exp1={.args_name=exp1};
    test_builtin(&sh,&cmd_exp1,(int(*)(t_shell*,t_cmd*))builtin_export,"",0,"Export valid");

    /* UNSET */
    char *unset1[]={"PATH",NULL};
    t_cmd cmd_unset1={.args_name=unset1};
    test_builtin(&sh,&cmd_unset1,(int(*)(t_shell*,t_cmd*))builtin_unset,"",0,"Unset PATH");

    /* ENV */
    t_cmd cmd_env={.args_name=NULL};
    test_builtin(&sh,&cmd_env,(int(*)(t_shell*,t_cmd*))builtin_env,"USER=guest\nEDITOR=vim\nLANG=en_US.UTF-8\n",0,"Env print");

    /* ECHO */
    sh.exit_status=42;
    char *echo1[]={"$?",NULL};
    t_cmd cmd_echo1={.args_name=echo1};
    test_builtin(&sh,&cmd_echo1,(int(*)(t_shell*,t_cmd*))builtin_echo,"42\n",0,"Echo $?");

    char *echo2[]={"-n","NoNewline",NULL};
    t_cmd cmd_echo2={.args_name=echo2};
    test_builtin(&sh,&cmd_echo2,(int(*)(t_shell*,t_cmd*))builtin_echo,"NoNewline",0,"Echo -n");

    /* PWD */
    t_cmd cmd_pwd={.args_name=NULL};
    char cwd[PATH_MAX]; getcwd(cwd,sizeof(cwd));
    char expected_pwd[PATH_MAX+2]; snprintf(expected_pwd,sizeof(expected_pwd),"%s\n",cwd);
    test_builtin(&sh,&cmd_pwd,(int(*)(t_shell*,t_cmd*))builtin_pwd,expected_pwd,0,"PWD test");

    /* RESUMEN GLOBAL */
    printf("=== RESUMEN GLOBAL ===\n");
    printf("Tests totales: %d | Pasados: %d | Fallidos: %d\n",test_res.total,test_res.passed,test_res.total-test_res.passed);

    /* Libera entorno */
    for(int i=0; sh.env[i]; i++) free(sh.env[i]);
    free(sh.env);

    return 0;
}
