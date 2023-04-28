/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/04/28 13:54:54 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/parsing.h"

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

static int analyze_line(char *all_line, t_all *all)
{
    int res;
    int i;
    char **splitted;

    i = 0;
    res = have_pipes(all_line);
    // printf("all_line %s\n", all_line);
    if(clean_all_line(all_line, &all->quotes) != 0)
        return(1);
    splitted = ft_split(all_line, '|');
    // clean_args(splitted); //doblepuntero
    while (i < (res + 1) && splitted[i])
    {
        all->node = lst_new(splitted[i]);
        lst_add_back(&all->node, all->node);
        all->node->args = ft_split(splitted[i], ' ');
        all->node->cmd = all->node->args[0];
        all->node = all->node->next;
        i++;
    }
    return(0);
    //free (splitted) while 
    //free (pipes node args) while
}

void    exec_cmd(t_all *all)
{
    if (ft_strncmp(all->node->cmd, "echo", 4) == 0)
        exec_echo(all->node);
    else if (ft_strncmp(all->node->cmd, "cd", 2) == 0)
        printf("he entradoooo CD\n");
    else if (ft_strncmp(all->node->cmd, "pwd", 3) == 0)
        printf("he entradoooo PWD \n");
    else if (ft_strncmp(all->node->cmd, "export", 6) == 0)
        printf("he entradoooo EXPORT \n");
    else if (ft_strncmp(all->node->cmd, "unset", 5) == 0)
        printf("he entradoooo UNSET \n");
    else if (ft_strncmp(all->node->cmd, "env", 3) == 0)
        printf("he entradoooo ENV \n");
        // exec_env(all->env);
    else if (ft_strncmp(all->node->cmd, "exit", 4) == 0)
        printf("he entradoooo EXIT \n");
    else
        printf("hemos d eencontar el path de los otros\n");
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
 
    t_all *all;
    
    // line = NULL;
    all = malloc(sizeof(t_all));
    if(!all)
        exit(0);
    all->env = env;
    while (1)
    {
        // get_env();
        all->all_line = get_line();
        if(analyze_line(all->all_line, all) == 0)
        {
            exec_cmd(all);
            free(all->all_line); //readline hace malloc
        }
    }
    return (0);
}