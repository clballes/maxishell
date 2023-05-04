/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/04 18:40:11 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
//Esta funcion comprueba si hay comillas abiertas y panda un error si es que hay
int	have_open_close_quotes(char *line, t_all *all)
{
	all->quotes.index = 0;
	all->quotes.has_quote = 0;
	while (line[all->quotes.index] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, ft_strlen(line) - 1);
		all->quotes.index++;
	}
	if (all->quotes.has_quote == 1)
	{
		printf("> you should close the quoting\n");
		return (1);
	}
	return (0);
}

int	ft_is_space(char c)
{
	if(c == 32 || c == '\f'|| c =='\n' || c == '\r' || c == '\t' || c == '\v')
		return(1);
	return (0);
}

//limpia la linea de comandos  si encuentra 
void	clean_spaces_line(char *all_line, t_all *all)
{
	int i;
	int j;
	
	j = 0;
	i = 0;
	while (all_line[i])
	{
		
		if (ft_is_space(all_line[i]) && !is_in_quottes(all_line, all, i))
		{
			all_line[j] = 32;
			i++;
			j++;
		}
		while (ft_is_space(all_line[i]) && !is_in_quottes(all_line, all, i))
			i++;
		all_line[j]= all_line[i];
		j++;
		i++; 
	}
	all_line[j] =  '\0';
}


// limpia la linea y analiza si es correcta
int	valid_line(char *all_line, t_all *all)
{
	if (have_open_close_quotes(all_line, all) != 0)
		return (1);
	printf("ANTES de limpiar:%s\n", all->all_line);
	clean_spaces_line(all->all_line, all);
	printf("DESPUES de limpiar:%s\n", all->all_line);
	
	return (0);
}
