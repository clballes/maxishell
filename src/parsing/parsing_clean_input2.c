/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean_input2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:04:27 by codespace         #+#    #+#             */
/*   Updated: 2023/05/22 17:10:55 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include <stdbool.h>

char	type_of_quottes(char *line, t_all *all, int i)
{
	int	j;

	all->quotes.found = '\0';
	all->quotes.has_quote = 0;
	j = 0;
	while (j <= i)
	{
		if ((line[j] == '\"' || line[j] == '\'') )
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
		}
		j++;
	}
	return (all->quotes.found);
}
// Esta funcion examina desde el inicio hasta el caracter con index i si 
// encuentra que ese caracter esta entre comillas activa has_quote y 
//devuelve 1 sino esta  entre comillas devuelve 0
int	is_in_quottes(char *line, t_all *all, int i)
{
	int	j;

	all->quotes.has_quote = 0;
	all->quotes.found = '\0';
	j = 0;
	while (j <= i)
	{
		if ((line[j] == '\"' || line[j] == '\'') )
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
		}
		j++;
	}
	return (all->quotes.has_quote);
}


