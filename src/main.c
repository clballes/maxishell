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
    free(line);
}

static void analyze_line(char *line, t_cmd *builtins)
{
    char **splitted;
    int i;
    int count;

    i = 1;
    count = 0;
    splitted = ft_split(line, ' ');
    while(*splitted[count] != '\0' && **splitted != '\0')
    {
        printf("%d\n", count);
        count++;
    }
    builtins->cmd = splitted[0];
    builtins->args = malloc(sizeof(char *) * count);
    while(splitted[i] && *splitted)
    {
        // printf("holaaaa\n");
        builtins->args[i - 1] = splitted[i];
        printf("%s\n", builtins->args[i - 1]);
        i++;
    }
    // free(splitted[i]);
    // free(builtins->args);
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
    }
    return (0);
}