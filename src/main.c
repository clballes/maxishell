/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/04/25 17:01:59 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int   have_pipes(char *line)
{   
    int i;
    int count;
    
    i = 0;
    count = 0;
    while(line[i] != '\0')
    {
        if (line[i] == '|')
            count++;
        i++;
    }
    return(count);
}

static char    *get_line()
{
    char *line;
    const char *prompt;

    prompt = "Bienvenid@ a Maxishell: ";
    line = readline(prompt);
    if (!line)
        exit(0); //funcion de error
    //limpiar
    return (line);
}

static void analyze_line(char *line, t_cmd *builtins, t_pipes *pipes)
{
    int res;

    res = 0;
    res = have_pipes(line);
    printf("Tengo %d pipes\n",res);



    
     char **splitted;
    int i;
    // int count;

    i = 0;
    // count = 0;
    
    splitted = ft_split(line, '|');
    // pipes->node = builtins;
    pipes->node = malloc(sizeof (t_cmd) * (res + 1));
    while (i < res + 1)
    {
        pipes->node = lst_new(splitted[i]);
        lst_add_back(&builtins, pipes->node);
        printf("dentro del while%s\n",pipes->node->cmd);
        i++;
    }
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




    
    builtins->args = ft_split(line, ' ');
    builtins->cmd = builtins->args[0];
}


void    exec_cmd(t_cmd *builtins)
{
    if (ft_strncmp(builtins->cmd, "echo", 4) == 0)
        printf("he entradoooo ECHOOO \n");
    else if (ft_strncmp(builtins->cmd, "cd", 2) == 0)
        printf("he entradoooo CD\n");
    else if (ft_strncmp(builtins->cmd, "pwd", 3) == 0)
        printf("he entradoooo PWD \n");
    else if (ft_strncmp(builtins->cmd, "export", 6) == 0)
        printf("he entradoooo EXPORT \n");
    else if (ft_strncmp(builtins->cmd, "unset", 5) == 0)
        printf("he entradoooo UNSET \n");
    else if (ft_strncmp(builtins->cmd, "env", 3) == 0)
        printf("he entradoooo ENV \n");
    else if (ft_strncmp(builtins->cmd, "exit", 4) == 0)
        printf("he entradoooo EXIT \n");
    else
        printf("hemos d eencontar el path de los otros\n");
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *line;
    t_cmd *builtins;
    t_pipes *pipes;
    
    line = NULL;
    builtins = malloc(sizeof(t_cmd));
    if(!builtins)
        exit(0);
    pipes = malloc(sizeof(t_pipes));
    if(!pipes)
        exit(0);
    builtins->env = env;
    while (1)
    {
        line = get_line();
        analyze_line(line, builtins, pipes);
        exec_cmd(builtins);
        free(line);
    }
    return (0);
}