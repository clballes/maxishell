/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:17:56 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/14 19:06:24 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

//mirar si  la redireccion tiene la sintaxis correcta si nos encontramos < y justo depues > o < y justo depues > entonces hay que lanzar un error 
// minishell: syntax error near unexpected token `<'

//Esta te devuelve cual es el caracter opuesto al que encuentras
static char	is_redi_opp(char c)
{
	char redi_opp;
	
	redi_opp = '\0';
	if(c == '<')
		redi_opp = '>';	
	else if(c == '>')
		redi_opp = '<';
	return(redi_opp);
}


int syntax_invalid_after_redir(char c, char redi, char redi_opp, t_all *all)
{
	if(c == '<')
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if(c == '>')
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if(c == '\0')
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	else if(c == '|')
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if(c == redi_opp && redi == '>')
		printf("minishell: syntax error near unexpected token `%c'\n", redi_opp);
	else
		return(0);
	all->exit = 2;
	return(1);
}

// si despues del caracter que encuentras esta el opuesto hay un error de syntax,e xcepto si es <>
int	syntax_redir_ok(char *line, t_all *all)
{
	int i;
	char redi_opp;
	char redi;
	i = -1;
	// printf("la line es %s\n", line);
	while (line[++i] != '\0')
	{
		if((line[i] == '<' || line[i] == '>')&& !is_in_quottes(line, all, i))
		{

			redi = line[i];
			redi_opp = is_redi_opp(line[i]);
			i++;
			if (line[i] == redi)
				i++;
			while (ft_is_space(line[i]))
				i++;
			if (syntax_invalid_after_redir(line[i], redi, redi_opp, all) != 0)
				return(1);
		}
	}
	return(0);
}
