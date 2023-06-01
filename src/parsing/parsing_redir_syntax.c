/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:17:56 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/01 11:22:35 by albagarc         ###   ########.fr       */
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

// si despues del caracter que encuentras esta el opuesto hay un error de syntax
int	syntax_redir_ok(char *line, t_all *all)
{
	int i;
	char redi_opp;
	
	i = -1;
	while (line[++i] != '\0')
	{
		if((line[i] == '<' || line[i] == '>')&& !is_in_quottes(line, all, i))
		{
			redi_opp = is_redi_opp(line[i]);
			i++;
			while(ft_is_space(line[i]))
				i++;
			if(line[i]== redi_opp)
			{
				printf("minishell: syntax error near unexpected token `<'\n");
				return(1);
			}
		}
	}
	return(0);
}