#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h> // para isalpha y isalnum

// ENUM

typedef enum e_token_type
{
    TOKEN_CMD,
    TOKEN_PIPE,
    TOKEN_REDIR
} token_type;

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
    char **argv;
    char *path;
    char *infile; 
    char *outfile;
    char *heredoc_word;
    int is_heredoc;
    t_builtin_type builtin_type;
    int append;
    int has_pipe;
    struct s_cmd *next;
} t_cmd;

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
    char *path;
    char **argv;
    int infile_fd;
    int outfile_fd;
    int is_builtin;
    t_builtin_type builtin_type;
    t_cmd *original;
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
} t_shell;

// GLOBALS
extern volatile sig_atomic_t handler;
extern int g_status;

// =====================
// FUNCIONES AUXILIARES
// =====================

// liberar array de strings
void free_dblptr(char **ptr)
{
    if (!ptr) return;
    for (int i = 0; ptr[i]; i++)
        free(ptr[i]);
    free(ptr);
}

// strncmp limitado
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;
    while (i < n && s1[i] && s1[i] == s2[i])
        i++;
    if (i == n)
        return 0;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

// Funciones de strings
size_t ft_strlen(const char *s) { size_t i=0; while (s&&s[i]) i++; return i; }
char *ft_strdup(const char *s) { if(!s) return NULL; size_t l=ft_strlen(s); char*dup=malloc(l+1); if(!dup) return NULL; for(size_t i=0;i<l;i++) dup[i]=s[i]; dup[l]='\0'; return dup; }
char *ft_substr(const char *s, unsigned int start, size_t len){if(!s)return NULL; size_t sl=ft_strlen(s); if(start>=sl)return ft_strdup(""); if(start+len>sl)len=sl-start; char*sub=malloc(len+1); if(!sub)return NULL; for(size_t i=0;i<len;i++) sub[i]=s[start+i]; sub[len]='\0'; return sub;}
int ft_strcmp(const char *s1, const char *s2){while(*s1 && *s1==*s2){s1++;s2++;} return *(unsigned char*)s1 - *(unsigned char*)s2;}
int ft_isalpha(int c){return isalpha(c);}
int ft_isalnum(int c){return isalnum(c)||c=='_';}
char *ft_strchr(const char *s,int c){return strchr(s,c);}
char *ft_strjoin(const char *a,const char *b){size_t la=ft_strlen(a),lb=ft_strlen(b); char*res=malloc(la+lb+1); if(!res)return NULL; size_t i=0; for(size_t j=0;j<la;j++) res[i++]=a[j]; for(size_t j=0;j<lb;j++) res[i++]=b[j]; res[i]='\0'; return res;}
char **ft_split(const char *s,char c){char **res=malloc(sizeof(char*)*2); res[0]=ft_strdup(s); res[1]=NULL; return res;}
char *ft_strjoin3(const char *a,const char *b,const char *c){size_t la=ft_strlen(a),lb=ft_strlen(b),lc=ft_strlen(c); char*res=malloc(la+lb+lc+1); if(!res)return NULL; size_t i=0; for(size_t j=0;j<la;j++) res[i++]=a[j]; for(size_t j=0;j<lb;j++) res[i++]=b[j]; for(size_t j=0;j<lc;j++) res[i++]=c[j]; res[i]='\0'; return res; }

// =====================
// ENV HELPERS
// =====================

int env_get(char **env,const char *key){int i; size_t len; if(!env||!key)return -1; len=ft_strlen(key); i=0; while(env[i]){if(!ft_strncmp(env[i],key,len)&&env[i][len]=='=')return i;i++;} return -1;}
static int env_replace(char **env,int idx,const char *var){char*nv=ft_strdup(var); if(!nv)return -1; free(env[idx]); env[idx]=nv; return 0;}
static int env_add(char ***env,const char *var){char**ne; int i=0; while(*env&&(*env)[i])i++; ne=malloc(sizeof(char*)*(i+2)); if(!ne)return -1; i=0; while(*env&&(*env)[i]){ne[i]=(*env)[i]; i++;} ne[i]=ft_strdup(var); if(!ne[i]){free(ne); return -1;} ne[i+1]=NULL; free(*env); *env=ne; return 0;}
int env_set(char ***env,const char *var){int idx;if(!env||!var)return -1; idx=env_get(*env,var); if(idx!=-1)return env_replace(*env,idx,var); return env_add(env,var);}
int env_add_empty(char ***env,const char *name){char*tmp=ft_strjoin(name,"="); int ret; if(!tmp)return -1; ret=env_add(env,tmp); free(tmp); return ret;}
char **copy_env(char **env){int i=0; while(env&&env[i]) i++; char**new=malloc(sizeof(char*)*(i+1)); if(!new)return NULL; i=0; while(env&&env[i]){new[i]=ft_strdup(env[i]); if(!new[i]){while(--i>=0) free(new[i]); free(new); return NULL;} i++;} new[i]=NULL; return new;}

// =====================
// FUNCIONES DE BUILTINS
// =====================

// Echo
static int is_n_flag(char *arg){if(!arg||arg[0]!='-'||arg[1]!='n')return 0; int i=2; while(arg[i]=='n')i++; return arg[i]=='\0';}
int builtin_echo(t_shell *sh, t_cmd *cmd){int i=1,print_newline=1; while(cmd->argv[i]&&is_n_flag(cmd->argv[i])){print_newline=0;i++;} while(cmd->argv[i]){printf("%s",cmd->argv[i]); if(cmd->argv[i+1])printf(" "); i++;} if(print_newline) printf("\n"); sh->last_status=0; return sh->last_status;}

// PWD
int builtin_pwd(t_shell *sh, t_cmd *cmd){char *cwd; (void)cmd; cwd=getcwd(NULL,0); if(cwd){printf("%s\n",cwd); free(cwd); sh->last_status=0;}else{perror("minishell: pwd"); sh->last_status=1;} return sh->last_status;}

// Env
int builtin_env(t_shell *sh, t_cmd *cmd){int i; (void)cmd; if(!sh||!sh->our_envp)return 1; i=0; while(sh->our_envp[i]){printf("%s\n",sh->our_envp[i]); i++;} sh->last_status=0; return 0;}

// Export
// (Mantengo todas tus funciones export_* exactas)
char *get_var_name(const char *arg){int i=0; while(arg[i]&&arg[i]!='=')i++; return ft_substr(arg,0,i);}
int is_valid_identifier(const char *str){int i;if(!str||!str[0]||str[0]=='=')return 0;if(!ft_isalpha(str[0])&&str[0]!='_')return 0; i=1; while(str[i]&&str[i]!='='){if(!ft_isalnum(str[i])&&str[i]!='_')return 0;i++;} return 1;}
void print_export(char *var){int i=0; if(!var||!ft_strcmp(var,"_="))return; printf("declare -x "); while(var[i]&&var[i]!='=')printf("%c",var[i++]); if(var[i]=='=')printf("=\"%s\"",var+i+1); printf("\n");}
void export_one(t_shell *sh,char *arg,int *has_error){char*name; int idx; if(!is_valid_identifier(arg)){fprintf(stderr,"minishell: export: `%s': not a valid identifier\n",arg); *has_error=1; return;} name=get_var_name(arg); idx=env_get(sh->our_envp,name); if(ft_strchr(arg,'=')){if(env_set(&sh->our_envp,arg)!=0)*has_error=1;} else if(idx==-1){if(env_add_empty(&sh->our_envp,name)!=0)*has_error=1;} free(name);}
int export_print(t_shell *sh){char **sorted; int i; sorted=copy_env(sh->our_envp); if(!sorted)return 1; i=0; while(sorted[i]){print_export(sorted[i]); free(sorted[i]); i++;} free(sorted); return 0;}
int export_args(t_shell *sh,t_cmd *cmd){int i=1,has_error=0; while(cmd->argv[i]){export_one(sh,cmd->argv[i],&has_error); i++;} return has_error?1:0;}
int builtin_export(t_shell *sh,t_cmd *cmd){if(!cmd->argv[1])sh->last_status=export_print(sh); else sh->last_status=export_args(sh,cmd); return sh->last_status;}

// Unset
static void shift_env_vars(char **env,int pos){while(env[pos+1]){env[pos]=env[pos+1]; pos++;} env[pos]=NULL;}
static void unset_single_var(char *var_name,char **env){int j,len; j=0; len=ft_strlen(var_name); while(env[j]){if(!ft_strncmp(var_name,env[j],len)&&(env[j][len]=='='||env[j][len]=='\0')){free(env[j]); shift_env_vars(env,j); break;} j++;}}
int builtin_unset(t_shell *sh,t_cmd *cmd){int i; if(!sh||!cmd||!cmd->argv)return 1; i=1; while(cmd->argv[i]){unset_single_var(cmd->argv[i],sh->our_envp); i++;} sh->last_status=0; return 0;}

// CD (manteniendo tu lógica, pero usando get_home_cached y update_environment)
char *get_local_env(const char *key,char **env){int idx; if(!key||!env)return NULL; idx=env_get(env,key); if(idx==-1)return NULL; return env[idx]+ft_strlen(key)+1;}
char *get_home_cached(t_shell *sh){char *home=get_local_env("HOME",sh->our_envp); if(!home||home[0]=='\0')return sh->cd_home; if(!sh->cd_home||ft_strcmp(sh->cd_home,home)!=0){free(sh->cd_home); sh->cd_home=ft_strdup(home); if(!sh->cd_home){fprintf(stderr,"minishell: cd: malloc failed\n"); sh->last_status=1; return NULL;}} return sh->cd_home;}
int needs_free(char *arg){if(!arg)return 0; return !(ft_strcmp(arg,"-")==0||ft_strcmp(arg,"~")==0);}
void update_environment(t_shell *sh,char *oldpwd,char *pwd){char*tmp; if(oldpwd){tmp=ft_strjoin("OLDPWD=",oldpwd); if(tmp) env_set(&sh->our_envp,tmp);} if(pwd){tmp=ft_strjoin("PWD=",pwd); if(tmp){env_set(&sh->our_envp,tmp); free(pwd);}}}
char *get_parent_from_pwd(t_shell *sh){char*pwd=get_local_env("PWD",sh->our_envp); if(!pwd)return NULL; char*parent=ft_strdup(pwd); if(!parent)return NULL; char*last_slash=strrchr(parent,'/'); if(!last_slash||last_slash==parent){free(parent); return ft_strdup("/");} *last_slash='\0'; return parent;}
char *calculate_logical_pwd(char *current,char *path){if(!current)return NULL; if(path[0]=='/')return ft_strdup(path); if(!ft_strcmp(path,"."))return ft_strdup(current); char*temp=ft_strjoin(current,"/"); char*res=ft_strjoin(temp,path); free(temp); return res;}
char *get_new_pwd(char *oldpwd,char *path,char *arg){char*pwd=getcwd(NULL,0); if(pwd)return pwd; if(!oldpwd)return NULL; if(needs_free(arg))return ft_strdup(path); if(arg)return calculate_logical_pwd(oldpwd,arg); return NULL;}
char *get_target_path(t_shell *sh,char *arg){if(!arg)return get_home_cached(sh); if(!ft_strcmp(arg,"-"))return get_local_env("OLDPWD",sh->our_envp); if(!ft_strcmp(arg,"~"))return get_home_cached(sh); if(!ft_strcmp(arg,".."))return get_parent_from_pwd(sh); return ft_strdup(arg);}
int change_directory(t_shell *sh,char *path,char *arg){if(chdir(path)<0){fprintf(stderr,"minishell: cd: %s",arg?arg:"HOME"); if(errno==EACCES)fprintf(stderr,": Permission denied\n"); else if(errno==ENOTDIR)fprintf(stderr,": Not a directory\n"); else fprintf(stderr,": No such file or directory\n"); return 0;} if(arg&&!ft_strcmp(arg,"-")) printf("%s\n",path); return 1;}
int builtin_cd(t_shell *sh,t_cmd *cmd){char*path; char*oldpwd; char*newpwd; if(!sh)return 1; oldpwd=get_local_env("PWD",sh->our_envp); if(!cmd->argv[1]) path=get_home_cached(sh); else path=cmd->argv[1]; if(!path){sh->last_status=1; return 1;} if(!change_directory(sh,path,cmd->argv[1])){sh->last_status=1; return 1;} newpwd=get_new_pwd(oldpwd,path,cmd->argv[1]); update_environment(sh,oldpwd,newpwd); sh->last_status=0; return 0;}

// Exit
static long long atoi_overflow_core(const char *str,int *error,int sign){long long result=0; int i=0; while(str[i]>='0'&&str[i]<='9'){long long d=str[i]-'0'; if(sign==1&&result>(LLONG_MAX-d)/10){*error=1; return 0;} if(sign==-1&&-result<(LLONG_MIN+d)/10){*error=1; return 0;} result=result*10+d; i++;} if(str[i]!='\0'){*error=1; return 0;} return result*sign;}
long long atoi_overflow(const char *str,int *error){int sign=1,i=0; if(error)*error=0; if(!str){if(error)*error=1; return 0;} while(str[i]==' '||(str[i]>='\t'&&str[i]<='\r')) i++; if(str[i]=='+'||str[i]=='-'){if(str[i]=='-')sign=-1; i++;} if(str[i]<'0'||str[i]>'9'){if(error)*error=1; return 0;} return atoi_overflow_core(&str[i],error,sign);}
static void handle_exit_invalid_arg(t_shell *sh,char *arg){printf("minishell: exit: %s: numeric argument required\n",arg); sh->last_status=2;}
static void handle_exit_too_many_args(t_shell *sh){printf("minishell: exit: too many arguments\n"); sh->last_status=1;}
void builtin_exit(t_shell *sh,t_cmd *cmd){long long exit_code; int invalid; printf("exit\n"); if(cmd->argv[1]&&cmd->argv[2]){handle_exit_too_many_args(sh); return;} if(cmd->argv[1]){exit_code=atoi_overflow(cmd->argv[1],&invalid); if(invalid){handle_exit_invalid_arg(sh,cmd->argv[1]); exit(2);} exit((int)(exit_code%256));} exit(sh->last_status);}

// =====================
// DETECT & EXEC BUILTIN
// =====================
void detect_builtin(t_cmd *cmd){if(!cmd||!cmd->argv||!cmd->argv[0])return; if(ft_strcmp(cmd->argv[0],"pwd")==0)cmd->builtin_type=BI_PWD; else if(ft_strcmp(cmd->argv[0],"echo")==0)cmd->builtin_type=BI_ECHO; else if(ft_strcmp(cmd->argv[0],"env")==0)cmd->builtin_type=BI_ENV; else if(ft_strcmp(cmd->argv[0],"export")==0)cmd->builtin_type=BI_EXPORT; else if(ft_strcmp(cmd->argv[0],"unset")==0)cmd->builtin_type=BI_UNSET; else if(ft_strcmp(cmd->argv[0],"cd")==0)cmd->builtin_type=BI_CD; else if(ft_strcmp(cmd->argv[0],"exit")==0)cmd->builtin_type=BI_EXIT; else cmd->builtin_type=BI_NONE;}
int exec_builtin(t_shell *sh,t_cmd *cmd){int status; if(!cmd||!sh)return 1; detect_builtin(cmd); status=0; if(cmd->builtin_type==BI_PWD)status=builtin_pwd(sh,cmd); else if(cmd->builtin_type==BI_ECHO)status=builtin_echo(sh,cmd); else if(cmd->builtin_type==BI_ENV)status=builtin_env(sh,cmd); else if(cmd->builtin_type==BI_EXPORT)status=builtin_export(sh,cmd); else if(cmd->builtin_type==BI_UNSET)status=builtin_unset(sh,cmd); else if(cmd->builtin_type==BI_CD)status=builtin_cd(sh,cmd); else if(cmd->builtin_type==BI_EXIT){builtin_exit(sh,cmd); return sh->last_status;} else status=1; sh->last_status=status; return status;}

// =====================
// RUN TEST
// =====================
void run_test(t_shell *sh,char **argv,int (*builtin)(t_shell*,t_cmd*),char*name){t_cmd cmd; memset(&cmd,0,sizeof(t_cmd)); cmd.argv=argv; printf("=== %s ===\n",name); exec_builtin(sh,&cmd); printf("status -> %d\n\n",sh->last_status);}

// =====================
// MAIN
// =====================
int main(int argc,char**envp)
{
    t_shell sh;
    (void)argc;
    memset(&sh,0,sizeof(t_shell));
    sh.our_envp=copy_env(envp);
    sh.last_status=0;

    printf("=== TEST BUILTINS ===\n\n");

    char *echo1[]={"echo","hola","mundo",NULL};
    run_test(&sh,echo1,builtin_echo,"echo hola mundo");

    char *echo2[]={"echo","-n","hola",NULL};
    run_test(&sh,echo2,builtin_echo,"echo -n hola");

    char *pwd_cmd[]={"pwd",NULL};
    run_test(&sh,pwd_cmd,builtin_pwd,"pwd");

    char *env_cmd[]={"env",NULL};
    run_test(&sh,env_cmd,builtin_env,"env");

    char *export_cmd[]={"export","TEST=42",NULL};
    run_test(&sh,export_cmd,builtin_export,"export TEST=42");

    run_test(&sh,env_cmd,builtin_env,"env after export");

    char *unset_cmd[]={"unset","TEST",NULL};
    run_test(&sh,unset_cmd,builtin_unset,"unset TEST");

    char *cd_cmd[]={"cd","/",NULL};
    run_test(&sh,cd_cmd,builtin_cd,"cd /");

    run_test(&sh,pwd_cmd,builtin_pwd,"pwd after cd");

    printf("=== FIN TESTS ===\n");

    free_dblptr(sh.our_envp);
    free(sh.cd_home);

    return 0;
}