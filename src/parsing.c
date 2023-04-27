/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/04/27 13:12:20 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int have_open_close_quotes(char *cmd_line, char quote)
{
    int i;
    int has_quote;


    i = 0;
    has_quote= 0;
   
    while(cmd_line[i] != '\0')
    {
        if(cmd_line[i] == quote)
        {
            has_quote++;
        }
        i++;
    }
    if(has_quote % 2 != 0)
    {
        printf("> you should close the quoting\n");
        return(1);
    }
    return(0);
}


int clean_all_line(char *all_line)
{
    if (have_open_close_quotes(all_line, 34) != 0)
        return(1);
    if (have_open_close_quotes(all_line, 39) != 0)
        return(1); 
    return (0);      
}

// void clean_args(char **command_line)
// {
//     int i;

//     i = 0;
//     while(command_line)
//     {
//         have_open_close_quotes(command_line[i]);
//     }
// }
