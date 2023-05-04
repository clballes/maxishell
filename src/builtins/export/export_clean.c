/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:21 by clballes          #+#    #+#             */
/*   Updated: 2023/05/03 15:07:22 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"


//funcions repetides
// int	check_repeat()
// {

// }

int	check_equal(t_cmd *node)
{
	int	i;
	int	j;

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

int	check_arg(char **args)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_prohibited(args[i][j], j) == 1)
			{
				printf("bash: export: %s: not a valid identifier\n", args[i]);
				return (1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}