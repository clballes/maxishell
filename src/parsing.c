/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/04/26 12:53:12 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        i++
    }
}

void clean_args(char **command_line)
{
    int i;

    i = 0;
    while(command_line)
    {
        have_open_close_quotes(command_line[i]);
    }
}
