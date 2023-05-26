/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 07:38:31 by codespace         #+#    #+#             */
/*   Updated: 2023/05/23 13:37:02 by albagarc         ###   ########.fr       */
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

	search_value = dolar_search_value(str + 1);
	expanded_value = search_in_env(all->list_env, search_value);
	after = ft_strjoin(expanded_value, str + len_search_value(str) + 1, 1, 0);
	free(search_value);
	return (after);
}

char	*manage_dolar_number(char *str)
{	
	char	*after;

	after = str + 2;
	return (ft_strdup(after));
}

char	*expand_dolar(char *str, t_all *all)
{
	char	*before;
	char	*after;
	int		j;
	char	quo;

	j = -1;
	after = NULL;
	while (str[++j] != '\0')
	{
		quo = type_of_quottes(str, all, j);
		if (str[j] == '$' && (!is_in_quottes(str, all, j) || quo == '\"'))
		{
			before = ft_substr(str, 0, j);//if before == NULL liberamos listenv listcmd y all_line
			if (str[j + 1] == '?')
				after = manage_dolar_exit(str + j, all);
			else if (str[j + 1] >= '0' && str[j + 1] <= '9')
				after = manage_dolar_number(str + j);
			else if (is_valid_char(str[j + 1]))
				after = manage_dolar_env(str + j, all);
			else
			{
				free (before);
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
