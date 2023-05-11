/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:21 by clballes          #+#    #+#             */
/*   Updated: 2023/05/04 10:20:00 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

// int	check_equal(t_cmd *node)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	node->equal = 0;
// 	while (node->args[i])
// 	{
// 		j = 0;
// 		while (node->args[i][j])
// 		{
// 			if (node->args[i][j] == '=' && node->args[i][j - 1] != '=')
// 				node->equal++;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (node->equal);
// }

void	check_arg(t_all *all, char *arg)
{
	int	i;

	all->node->equal = 0;
	i = 1;
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

int	ft_prohibited(char c, int j, int equal, int concat)
{
	if (c == '=')
		return (0);
	else if ((j == 0) && (concat == 0) && (equal == 0) && ((c >= 33 && c <= 64)
			|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126)))
		return (1);
	else if ((j != 0) && (equal == 0) && (concat == 0) && ((c >= 34 && c <= 47)
			|| (c >= 58 && c <= 64) || (c >= 91 && c <= 96)
			|| (c >= 123 && c <= 126)))
		return (1);
	else if ((equal == 1) && (j != 0) && (concat == 1))
		return (0);
	return (0);
}