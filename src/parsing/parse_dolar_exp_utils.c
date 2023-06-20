/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 07:38:31 by codespace         #+#    #+#             */
/*   Updated: 2023/06/20 18:39:40 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

int	expand_conditions(char *str, t_all *all, int j)
{
	if (str[j + 1] == '?' || (str[j + 1] >= '0' && str[j + 1] <= '9') || \
	is_valid_char(str[j + 1]))
	{
		return (1);
	}
	if ((str[j + 1] == '\'' || str[j + 1] == '\"') && \
		!is_in_quottes(str, all, j))
		return (1);
	return (0);
}

char	*dolar_special_meaning(char *str, t_all *all, char *full_str, int j)
{
	char	*after;

	after = NULL;
	if (str[1] == '?')
		after = manage_dolar_exit(str, all);
	else if (str[1] >= '0' && str[1] <= '9')
		after = manage_dolar_number(str);
	else if (is_valid_char(str[1]))
		after = manage_dolar_env(str, all);
	else if ((str[1] == '\'' || str[1] == '\"') && \
		!is_in_quottes(full_str, all, j))
		after = ft_strdup(full_str + j + 1);
	return (after);
}

char	*expand_dolar(char *str, t_all *all)
{
	char	*before;
	char	*after;
	int		j;

	j = -1;
	while (str[++j] != '\0')
	{	
		if (str[j] == '$' && (!is_in_quottes(str, all, j) || \
			type_of_quottes(str, all, j) == '\"'))
		{
			before = ft_substr(str, 0, j);
			if (expand_conditions(str, all, j))
				after = dolar_special_meaning(str + j, all, str, j);
			else
			{
				free(before);
				continue ;
			}
			free(str);
			str = ft_strjoin(before, after, 1, 1);
			if (str[j] == '$')
				j--;
		}
	}
	return (str);
}
