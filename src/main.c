/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/04/25 11:03:38 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char    *get_line()
{
    char *line;
    const char *prompt;

    prompt = "Bienvenid@ a Maxishell: ";
    line = readline(prompt);
    if (!line)
        exit(0); //funcion de error
    return (line);
}

static void analyze_line(char *line, t_cmd *builtins)
{
    builtins->args = ft_split(line, ' ');
    builtins->cmd = builtins->args[0];
    // char **splitted;
    // int i;
    // int count;

    // i = 1;
    // count = 0;
    // printf("%s\n", builtins->args[1]);
    // while(splitted[count] != NULL)
    //     count++;
    // builtins->args = malloc(sizeof(char *) * (count - 1));
    // while(splitted[i] && *splitted)
    // {
    //     builtins->args[i - 1] = splitted[i];
    //     // printf("%s\n", builtins->args[i - 1]);
    //     i++;
    // }
    // free(splitted[i]); liberar con whhile -- crear funcion
    // free(builtins->args);
}

void    exec_cmd(t_cmd *builtins)
{
    printf("%s\n", builtins->cmd);
    //strcompare
    // if (builtins->cmd == "echo")
    //     printf("he entradoooo ECHOOO \n");
    // else if (builtins->cmd == "cd")
    //     printf("he entradoooo CD\n");
    // else if (builtins->cmd == "pwd")
    //     printf("he entradoooo PWD \n");
    // else if (builtins->cmd == "export")
    //     printf("he entradoooo EXPORT \n");
    // else if (builtins->cmd == "unset")
    //     printf("he entradoooo UNSET \n");
    // else if (builtins->cmd == "env")
    //     printf("he entradoooo ENV \n");
    // else if (builtins->cmd == "exit")
    //     printf("he entradoooo EXIT\n");
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *line;
    t_cmd *builtins;

    line = NULL;
    builtins = malloc(sizeof(t_cmd));
    if(!builtins)
        exit(0);
    builtins->env = env;
    while (1)
    {
        line = get_line();
        analyze_line(line, builtins);
        exec_cmd(builtins);
        free(line);
    }
    return (0);
}