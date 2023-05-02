/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:04:27 by codespace         #+#    #+#             */
/*   Updated: 2023/05/02 09:51:39 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include <stdbool.h>

//Esta funcion recorre la string si encuentra quotes se activa una variable para que 
// en el caso de que haya un pipe dentro de comillas no nos lo coja como un real pipe
// Si encuentra un pipe real o ya no quedan pipes y estamos al final de la linea
// lo que hace es extraer la linea y guardar las nuevas posiciones para la proxima vez 
// que al crear un nodo se llame a esta función 
// Devuelve esa linea  que en la función de analize line lo introducimos como contenido del nodo
char   *content_list(char *line, bool init, t_all *all)
{   
    static int  i;
    static int  start;
    bool        active_quotes;
    char        *line_split_by_pipes;
    static int  count;
    
	line_split_by_pipes = NULL;
    if (init)
    {
        i = 0;
        start = 0;
        count = all->n_pipes;
    }
    active_quotes = false;
    while (line[i] != '\0')
    {
        // printf("llega a entrar? line[%d]=%c \n", i, line[i]);
        if (line[i] == '\"' || line[i] == '\'')
        {
            if (!active_quotes)
                active_quotes = true;
            else if (active_quotes)
                active_quotes = false;
        }
        if ((line[i] == '|' && !active_quotes) || (count == 0 && line[i+1] == '\0'))
        {
            // printf("n_pipes:%d\n", all->n_pipes);
            if(line[i+1] == '\0')
                line_split_by_pipes = ft_substr(line, start, i + 1 - start); // mirar por qué el +1
            else
                line_split_by_pipes = ft_substr(line, start, i - start); //TODO cada substring hace MALLOC HAY QUE HACER FREE
            count--;
            start = i + 1;
            i++;
            // printf("la linea es:%s\n ", line_split_by_pipes);
            break;  
        }
        i++;
    }
    return(line_split_by_pipes);
}

// static int analyze_line(char *all_line, t_all *all)
// {
//     int n_pipes;
//     int i;
//     int j;e
//     int k;
//     // char **splitted;

//     i = 0;
//     n_pipes = have_pipes(all_line);
//     
    
//     // printf("all_line %s\n", all_line);
//     if(clean_all_line(all_line, &all->quotes) != 0)
//         return(1);
//     while(all_line[i] != '\0')
//     {
//         while(all_line[i] == 32)
//             i++;
//         if(all_line[i] == 32)
//         {
//             k++;
//         }
//         else if (all_line[i] == '\'')
//         {
//             all->node = single_quote_mode(all_line, i, all->node);                       
//         }
//         else if (all_line[i] == '\"')
//         {
//             all->node = double_quote_mode(all_line, i, all->node);
//         }
//         else
//             all->node->args[k][j] = all_line[i];
        
//         i++;
//     }






    // splitted = ft_split(all_line, '|');
    // // clean_args(splitted); //doblepuntero
    // while (i < (res + 1) && splitted[i])
    // {
    //     all->node = lst_new(splitted[i]);
    //     lst_add_back(&all->node, all->node);
    //     all->node->args = ft_split(splitted[i], ' ');//aquí va la función que me va a separar los argumentos 
    //     all->node->cmd = all->node->args[0];
    //     all->node = all->node->next;
    //     i++;
    // }
    // return(0);
    //free (splitted) while 
    //free (pipes node args) while
// }

