/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:21 by clballes          #+#    #+#             */
/*   Updated: 2023/05/12 14:00:47 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	check_arg(t_all *all, char *arg)
{
	int	i;

	all->node->equal = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			all->list_env->concatenate = 1;
		if (arg[i] == '=')
			all->node->equal = 1;
		if (ft_prohibited(arg[i], i, all->node->equal,
				all->list_env->concatenate) == 1)
		{
			printf("bash: export: %s: not a valid identifier\n", arg);
			return ;
		}
		else
			i++;
	}
}
//export hola=a a mhauria de crear variable a la a
// mha odnat una seg fault raro
// si posem hola=a i despres hola el valor sharuai de quedar
int	ft_prohibited(char c, int index, int equal, int concat)
{
	if (c == '=' && (index != 0))
		return (0);
	else if ((index == 0) && (!(ft_isalpha(c))))
		return (1);
	// else if ((c == '=' || c == ' ' || ) && (index == 0))
	// 	return (1);
	// else if ((index == 0) && (concat == 0)
	// 	&& (equal == 0) && ((c >= 33 && c <= 64)
	// 		|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126)))
	// 	return (1);
	else if ((index != 0) && (equal == 0)
		&& (concat == 0) && ((c >= 34 && c <= 47)
			|| (c >= 58 && c <= 64) || (c >= 91 && c <= 96)
			|| (c >= 123 && c <= 126)))
		return (1);
	else if ((equal == 1) && (index != 0) && (concat == 1))
		return (0);
	return (0);
}
