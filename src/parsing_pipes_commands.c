/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:04:27 by codespace         #+#    #+#             */
/*   Updated: 2023/05/04 19:49:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include <stdbool.h>

// Esta funcion examina desde el inicio hasta el caracter con index i si 
// encuentra que ese caracter esta entre comillas activa has_quote y 
//devuelve 1 sino esta  entre comillas devuelve 0
int	is_in_quottes(char *line, t_all *all, int i)
{
	int	j;

	all->quotes.has_quote = 0;
	j = 0;
	while (j <= i)
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
		}
		j++;
	}
	return (all->quotes.has_quote);
}

// Esta funcion me extrae el comando que separan los pipes dependiendo 
// si es el ultimo o no
char	*save_line_depends_on_position(char *line, int start, int i)
{
	char	*line_to_return;

	if (line[i + 1] == '\0')
		line_to_return = ft_substr(line, start, i + 1 - start);
	else
		line_to_return = ft_substr(line, start, i - start); //TODO cada substring hace MALLOC HAY QUE HACER FREE
	return (line_to_return);
}

//Esta funcion recorre la string si encuentra quotes se activa una 
//variable para que en el caso de que haya un pipe dentro de comillas no nos lo
//coja como un real pipe Si encuentra un pipe real o ya no quedan pipes
//y estamos al final de la linea lo que hace es extraer la linea y guardar las 
//nuevas posiciones de i,count,start para que la proxima vez que al crear
//un nodo se llame a esta función siga por donde se quedo.
//Devuelve esa linea  que en la función de analize line lo introducimos 
//como contenido del nodo.
char	*content_list(char *line, bool init, t_all *all)
{
	static int	i;
	static int	start;
	char		*line_split_by_pipes;

	line_split_by_pipes = NULL;
	if (init)
	{
		i = 0;
		start = 0;
	}
	all->quotes.has_quote = 0;
	while (line[i] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
		if ((line[i] == '|' && !all->quotes.has_quote) || \
			(line[i + 1] == '\0'))
		{	
			line_split_by_pipes = save_line_depends_on_position(line, start, i);
			start = i + 1;
			i++;
			break ;
		}
		i++;
	}
	printf("linea %s\n", line_split_by_pipes);
	return (line_split_by_pipes);
}

void	divide_in_tokens(t_all *all)
{
	char	c;

	c = ' ';
	while (all->node)
	{
		all->node->args = ft_split_tokens(all->node->line, c, all);
		printf("%s\n", all->node->args[1]);
		all->node = all->node->next;
	}
}
