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

void	var(t_all *all)
{
	printf("el char es %s\n", all->env[29]);

	// temp = *list_env;
	// while (all->env[all->list_env->index])
	// {
	// 	printf("la string es : %s\n", env[list_env->index]);
	// 	// cont_name = ft_split(all->env[i], '=');
	// 	// temp = lst_new_env(cont_name[0], cont_name[1]);
	// 	// lst_add_back_env(&all->list_env, temp);
	// 	// free(cont_name);
	// 	// temp = temp->next;
	// 	// all->list_env->index++;
	// }

}

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