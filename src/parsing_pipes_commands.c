/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:04:27 by codespace         #+#    #+#             */
/*   Updated: 2023/05/04 12:26:29 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include <stdbool.h>
// Te devuelve 0 si no estas dentro de quotes y 1 si estas dentro de quotes
// int is_inside_quotting(const char *line, t_all *all, int i)
// {
// 		if (line[i] == '\"' || line[i] == '\'')
// 			{
// 				if (!all->quotes.has_quote)
// 				{
// 					all->quotes.has_quote = 1;
// 					all->quotes.found = line[i];
// 				}
// 				else if (all->quotes.has_quote && line[i] == all->quotes.found)
// 				{
// 					all->quotes.has_quote = 0;
// 					all->quotes.found = ' ';
// 				}
// 				printf("line[i]:%c:%d\n", line[i], all->quotes.has_quote);
// 			}
	

// 	return(all->quotes.has_quote);
// }


int is_inside_quotting(const char *line, t_all *all, int i)
{
	//se inicia la has_quote a cero
	all->quotes.has_quote=0;
	int j;

	j = 0;
	while(j <= i)
	{
		if (line[j] == '\"' || line[j] == '\'')
			{
				if (!all->quotes.has_quote)
				{
					all->quotes.has_quote = 1;
					all->quotes.found = line[j];
				}
				else if (all->quotes.has_quote && line[j] == all->quotes.found)
				{
					all->quotes.has_quote = 0;
					all->quotes.found = ' ';
				}
				printf("line[j]:%c:%d\n", line[j], all->quotes.has_quote);
			}
		j++;
	}
	return(all->quotes.has_quote);
}

// Esta funcion me extrae el comando que separan los pipes dependiendo si es el ultimo o no
char *save_line_depends_on_position(char *line, int start, int i)
{
	char *line_to_return;
	
	if(line[i + 1] == '\0')
        line_to_return = ft_substr(line, start, i + 1 - start);
    else
        line_to_return = ft_substr(line, start, i - start); //TODO cada substring hace MALLOC HAY QUE HACER FREE
	return(line_to_return);
}

//Esta funcion recorre la string si encuentra quotes se activa una variable para que 
// en el caso de que haya un pipe dentro de comillas no nos lo coja como un real pipe
// Si encuentra un pipe real o ya no quedan pipes y estamos al final de la linea
// lo que hace es extraer la linea y guardar las nuevas posiciones de i,count,start para que la proxima vez 
// que al crear un nodo se llame a esta función siga por donde se quedo.
// Devuelve esa linea  que en la función de analize line lo introducimos como contenido del nodo
char   *content_list(char *line, bool init, t_all *all)
{   
    static int  i;
    static int  start;
    char        *line_split_by_pipes;
    static int  count_pipes;
    
	line_split_by_pipes = NULL;
    if (init)
    {
        i = 0;
        start = 0;
        count_pipes = all->n_pipes;
    }
    all->quotes.has_quote = 0;
    while (line[i] != '\0')
    {
		all->quotes.has_quote = is_inside_quotting(line, all, i);
		printf("metiendo la info en los nodos line[i]:%c\n", line[i]);
        if ((line[i] == '|' && !all->quotes.has_quote) || (count_pipes == 0 && line[i + 1] == '\0'))
        {
			printf("estoy aqui???\n");
			line_split_by_pipes = save_line_depends_on_position(line, start, i);
            count_pipes--;
            start = i + 1;
            i++;
            break;  
        }
		i++;
    }
    return(line_split_by_pipes);
}

void	divide_in_tokens(t_all *all)
{
	char	c;
	
	c = ' ';
	while(all->node)
	{
		all->node->args = ft_split_tokens(all->node->line, c, all);
		printf("%s\n",all->node->args[1]);
		all->node = all->node->next;
	}
	
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

