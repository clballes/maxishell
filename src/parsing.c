/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/04 12:26:43 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

//Una vez que ya hemos encontrado la quote de inicio busca la de cierre
// t_quo *find_second_quote(t_quo *quotes, char *cmd_line)
// {
//     while(quotes->has_quote && cmd_line[quotes->index])
//         {
//             if(cmd_line[quotes->index + 1] == quotes->found)
//             {
//                 quotes->has_quote = 0;
//                 quotes->index++;
//                 break;
//             }
//             quotes->index++;
//         }
//     return (quotes);
// }

//Comprueba que todas las quotes están bien cerradas
int have_open_close_quotes(char *cmd_line, t_all *all)
{
    all->quotes.index = 0;
    all->quotes.has_quote = 0;
    while(cmd_line[all->quotes.index] != '\0')
    {
		all->quotes.has_quote= is_inside_quotting(cmd_line, all, ft_strlen(cmd_line)-1); //ft_strlen(cmd_line)-1 all->quotes.index
        // if(cmd_line[all->quotes.index] == '\"' || cmd_line[all->quotes.index] == '\'')
        // {
        //     all->quotes.found = cmd_line[all->quotes.index];
        //     all->quotes.has_quote = 1;
        // }
        // quotes = find_second_quote(quotes, cmd_line);
        all->quotes.index++;
        //if(!all->quotes.has_quote && cmd_line[all->quotes.index]== 32) para que me cuente el numero de argumentos
                // n_args++;           
    }
    if(all->quotes.has_quote  == 1)
    {
        printf("> you should close the quoting\n");
        return(1);
    }
    return(0);
}
//funcion que haga i++ desde que encuentra una quote hasta que termina esa misma quote

// limpia la linea y analiza si es correcta
int clean_all_line(char *all_line, t_all *all)
{
    if (have_open_close_quotes(all_line, all) != 0)
        return(1);
    
    
    return (0);      
}




