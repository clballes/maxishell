#include "../inc/minishell.h"
#include "../inc/builtins.h"

int    check_args(char **args)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while(args[i])
    {
        while(args[i][j])
        {
            if(ft_isdigit(args[i][j]) == 0)
            {
                printf("exit\n");
                printf("bash: exit: %s: numeric argument required\n", args[i]);
                return (1);
            }
            else
                j++;
        }
        i++;
    }
    return (0);
}

void    exec_exit(t_cmd *builtins)
{
    int i;

    i = 0;
    while(builtins->args[i])
        i++;
    if(check_args(builtins->args) == 0)
    {
        if (i > 2)
        {
            printf("exit\n");
            printf("bash: exit: too many arguments\n");
        }
        else
            printf("exit\n");
            exit(0);
    }
    else
        exit(0);
}