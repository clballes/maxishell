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
#include "../inc/builtins.h"

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
    return (line);
}

static void analyze_line(char *all_line, t_all *pipes)
{
    int res;
    int i;
    char **splitted;

    i = 0;
    res = have_pipes(all_line);
    splitted = ft_split(all_line, '|');
    // clean_args(splitted); //doblepuntero
    while (i < (res + 1) && splitted[i])
    {
        pipes->node = lst_new(splitted[i]);
        lst_add_back(&pipes->node, pipes->node);
        pipes->node->args = ft_split(splitted[i], ' ');
        pipes->node->cmd = pipes->node->args[0];
        pipes->node = pipes->node->next;
        i++;
    }
    //free (splitted) while 
    //free (pipes node args) while
}

void    exec_cmd(t_cmd *builtins)
{
    if (ft_strncmp(builtins->cmd, "echo", 4) == 0)
        exec_echo(builtins);
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
    t_all *all_cmd;
    
    line = NULL;
    all_cmd = malloc(sizeof(t_all));
    if(!all_cmd)
        exit(0);
    all_cmd->env = env;
    while (1)
    {
        line = get_line();
        analyze_line(line, all_cmd);
        exec_cmd(all_cmd->node);
        free(line); //readline hace malloc
    }
    return (0);
}