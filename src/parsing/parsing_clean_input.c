/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:39:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/14 19:12:43 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

//Esta funcion comprueba si hay comillas abiertas y manda un error si es que hay
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

// Devuelve uno si el caracter analizado es un espacio 
int	ft_is_space(char c)
{
	if (c == 32 || c == '\f' || c == '\n' || c == '\r' \
		|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

//limpia la linea de comandos  si encuentra 
void	clean_spaces_line(char *all_line, t_all *all)
{
	int	i;
	int	j;

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
		all_line[j] = all_line[i];
		j++;
		i++;
	}
	all_line[j] = '\0';
}

//tira error si despues del pipe no hay nada 
int	syntax_pipes_ok(char *line, t_all *all)
{
	int i;

	i = -1;
	while (line[++i] )
	{
		if(line[0] == '|')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",2);
			all->exit = 2;
			return(1);
		}
		if(line[i] == '|' && !is_in_quottes(line, all, i))
		{
			i++;
			while(ft_is_space(line[i]))
				i++;
		}
		if(line[i] == '\0')
		{
			ft_putstr_fd("> syntax error: Please write something after '|'\n",2);
			all->exit = 2;
			return(1);
		}
	}
	return (0);
} 

// limpia la linea y analiza si es correcta
int	valid_clean_line(char *all_line, t_all *all)
{
	if (have_open_close_quotes(all_line, all) != 0)
		return (1);
	if (syntax_redir_ok(all_line, all) != 0)
		return(1);
	if (syntax_pipes_ok(all_line, all) != 0)
		return(1);
	clean_spaces_line(all->all_line, all);
	return (0);
}
