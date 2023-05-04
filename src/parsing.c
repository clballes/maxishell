/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/04 16:41:20 by albagarc         ###   ########.fr       */
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

// limpia la linea y analiza si es correcta
int	clean_all_line(char *all_line, t_all *all)
{
	if (have_open_close_quotes(all_line, all) != 0)
		return (1);
	return (0);
}
