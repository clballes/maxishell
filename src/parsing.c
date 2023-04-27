/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/04/27 16:48:13 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int have_open_close_quotes(char *cmd_line, char quote)
// {
//     int i;
//     int has_quote;


//     i = 0;
//     has_quote = 0;
   
//     while(cmd_line[i] != '\0')
//     {
//         if(cmd_line[i] == quote)
//         {
//             has_quote++;
//         }
//         i++;
//     }
//     if(has_quote % 2 != 0)
//     {
//         printf("> you should close the quoting\n");
//         return(1);
//     }
//     return(0);
// }

int have_open_close_quotes(char *cmd_line)
{
    int i;
    int has_quote;
    char found;

    i = 0;
    has_quote = 0;
    while(cmd_line[i] != '\0')
    {
        if(cmd_line[i] == '\"' || cmd_line[i] == '\'')
        {
            found = cmd_line[i];
            has_quote = 1;
        }
        while(has_quote && cmd_line[i])
        {
            if(cmd_line[i+1] == found)
            {
                has_quote = 0;
                i++;
                break;
            }
            i++;
        }
        i++;
    }
    if(has_quote  == 1)
    {
        printf("> you should close the quoting\n");
        return(1);
    }
    return(0);
}

int clean_all_line(char *all_line)
{
    if (have_open_close_quotes(all_line) != 0)
        return(1);
    // if (have_open_close_quotes(all_line) != 0)
    //     return(1); 
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
