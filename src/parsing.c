/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/04/28 13:55:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

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
        quotes->index++;
    }
    if(quotes->has_quote  == 1)
    {
        printf("> you should close the quoting\n");
        return(1);
    }
    return(0);
}

int clean_all_line(char *all_line, t_quo *quotes)
{
    if (have_open_close_quotes(all_line, quotes) != 0)
        return(1);
    
    return (0);      
}


