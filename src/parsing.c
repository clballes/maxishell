/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/01 13:56:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

//Una vez que ya hemos encontrado la quote de inicio busca la de cierre
t_quo *find_second_quote(t_quo *quotes, char *cmd_line)
{
    while(quotes->has_quote && cmd_line[quotes->index])
        {
            if(cmd_line[quotes->index + 1] == quotes->found)
            {
                quotes->has_quote = 0;
                quotes->index++;
                break;
            }
            quotes->index++;
        }
    return (quotes);
}

//Comprueba que todas las quotes están bien cerradas
int have_open_close_quotes(char *cmd_line, t_quo *quotes)
{
    quotes->index = 0;
    quotes->has_quote = 0;
    while(cmd_line[quotes->index] != '\0')
    {
        if(cmd_line[quotes->index] == '\"' || cmd_line[quotes->index] == '\'')
        {
            quotes->found = cmd_line[quotes->index];
            quotes->has_quote = 1;
        }
        quotes = find_second_quote(quotes, cmd_line);
        quotes->index++;
        // if(!quotes->has_quote && cmd_line[quotes->index]== 32) para que me cuente el numero de argumentos
                // n_args++;           
    }
    if(quotes->has_quote  == 1)
    {
        printf("> you should close the quoting\n");
        return(1);
    }
    return(0);
}
//funcion que haga i++ desde que encuentra una quote hasta que termina esa misma quote

// limpia la linea y analiza si es correcta
int clean_all_line(char *all_line, t_quo *quotes)
{
    if (have_open_close_quotes(all_line, quotes) != 0)
        return(1);
    
    
    return (0);      
}


