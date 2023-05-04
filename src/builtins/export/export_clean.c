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

int	check_equal(t_cmd *node, t_all *all)
{
	int	i;
	int	j;

	(void)all;
	i = 1;
	node->equal = 0;
	while (node->args[i])
	{
		j = 0;
		while (node->args[i][j])
		{
			if (node->args[i][j] == '=' && node->args[i][j - 1] != '=')
				node->equal++;
			j++;
		}
		i++;
	}
	return (node->equal);
}

void	check_arg(t_all *all)
{
	int	i;
	int	j;

	j = 0;
	all->node->flag = 0;
	i = 1;
	while (all->node->args[i])
	{
		j = 0;
		while (all->node->args[i][j])
		{
			if (all->node->args[i][j] == '+' && all->node->args[i][j + 1] == '=')
				all->list_env->concatenate = 1;
			if (all->node->args[i][j] == '=')
				all->node->flag = 1;
			if (ft_prohibited(all->node->args[i][j], j, all->node->flag, all->list_env->concatenate) == 1)
			{
				printf("bash: export: %s: not a valid identifier\n", all->node->args[i]);
				return ;
			}
			else
				j++;
		}
		i++;
	}
}
