/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:15:31 by clballes          #+#    #+#             */
/*   Updated: 2023/06/26 12:24:06 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

char	*shlvl(char *cont_name)
{
	int		new_shlvl;
	char	*var;
	int		shl_level;

	shl_level = 1;
	new_shlvl = ft_atoi(cont_name);
	if (new_shlvl < 0)
		shl_level = -1;
	else if (new_shlvl > 999)
	{
		new_shlvl++;
		var = ft_itoa(new_shlvl);
		write_dyn_err("bash: warning: shell level (&) too high, resetting to 1",
			var);
		shl_level = 0;
	}
	else
		shl_level = ft_atoi(cont_name);
	shl_level++;
	free(cont_name);
	cont_name = ft_itoa(shl_level);
	return (cont_name);
}

void	change_shlvl(t_all *all, char *cont_name)
{
	all->exist = 1;
	if (cont_name == NULL)
		cont_name = "1";
	else
		cont_name = shlvl(cont_name);
}

void	add_shlvl(t_env *temp, t_all *all)
{
	temp = lst_new_env("SHLVL", "1");
	lst_add_back_env(&all->list_env, temp);
	temp->print = 1;
}
