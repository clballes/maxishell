#include "../inc/minishell.h"
#include "../inc/builtins.h"

int   exec_pwd(void)
{
   char pwd[1024];
   
   if (getcwd(pwd, sizeof(pwd)) != NULL)
       printf("%s\n", pwd);
    else
    {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}