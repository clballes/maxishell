/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:15:13 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/20 18:40:17 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

int	is_valid_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' )
		return (1);
	return (0);
}

char	*manage_dolar_exit(char *str, t_all *all)
{
	char	*after;

	after = NULL;
	after = ft_strjoin(ft_itoa(all->exit), str + 2, 1, 0);
	return (after);
}

char	*manage_dolar_env(char *str, t_all *all)
{
	char	*search_value;
	char	*expanded_value;
	char	*after;

	search_value = dolar_search_value(str + 1, all);
	expanded_value = search_in_env(all->list_env, search_value);
	after = ft_strjoin(expanded_value, \
		str + len_search_value(str, all) + 1, 1, 0);
	free(search_value);
	return (after);
}

char	*manage_dolar_number(char *str)
{	
	char	*after;

	after = str + 2;
	return (ft_strdup(after));
}
