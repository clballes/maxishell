/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:03:33 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/20 20:12:10 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

int	second_pipe_in_a_row(char *line, t_all *all);

int	print_error_pipe_syntax(char c, t_all *all)
{
	if (c == '|')
	{
		ft_putstr_fd("msh: syntax error near unexpected token `|'\n", 2);
		all->exit = 2;
	}
	if (c == '\0')
	{
		ft_putstr_fd("> syntax err: Please write something after '|'\n", 2);
		all->exit = 2;
	}
	return (1);
}

//tira error si despues del pipe no hay nada 
int	syntax_pipes_ok(char *line, t_all *all)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[0] == '|')
			return (print_error_pipe_syntax('|', all));
		if (line[i] == '|' && !is_in_quottes(line, all, i))
		{
			i++;
			while (ft_is_space(line[i]))
				i++;
			if (second_pipe_in_a_row(line + i, all))
				return (1);
		}
		if (line[i] == '\0')
			return (print_error_pipe_syntax('\0', all));
	}
	return (0);
}

//Busca si hay un segundo pipe seguido despues de otro pipe
int	second_pipe_in_a_row(char *line, t_all *all)
{
	int	i;

	i = 0;
	while (ft_is_space(line[i]))
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		all->exit = 2;
		return (1);
	}
	return (0);
}
