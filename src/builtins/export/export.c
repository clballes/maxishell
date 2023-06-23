/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:09 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 13:03:30 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	ft_repeat(t_all *all, char *res, char *arg, t_env *temp)
{
	while (temp)
	{
		if (ft_strncmp(temp->name, arg, ft_strlen(arg) + 1) == 0)
		{
			if (all->list_env->concatenate == 1)
			{
				if (temp->content && res != NULL)
				{
					free(arg);
					temp->content = ft_strjoin(temp->content, res, 1, 1);
				}
			}
			else if (all->list_env->concatenate == 0 || all->node->equal != 0
				|| (all->list_env->concatenate == 0 && res == NULL))
			{
				if (all->list_env->concatenate == 0 && all->node->equal != 0)
				{
					free(arg);
					free(temp->content);
					change_var_list(res, temp);
					temp->print = 1;
				}
			}
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	add_new(t_all *all, char *arg)
{
	char	*name;
	char	*name_value;
	int		equal;
	t_env	*temp;

	temp = all->list_env;
	name = extract_var_name(arg);
	name_value = extract_var_value(arg);
	equal = 0;
	if (ft_repeat(all, name_value, name, temp) == 1)
	{
		free_arr(all->env_array);
		all->env_array = list_to_double_pointer(&all->list_env, all);
		return ;
	}
	temp = lst_new_env(name, name_value);
	lst_add_back_env(&all->list_env, temp);
	if (name_value == NULL && all->node->equal == 0)
		temp->print = 0;
	else
		temp->print = 1;
	free_arr(all->env_array);
	all->env_array = list_to_double_pointer(&all->list_env, all);
	sort_list(&all->list_env);
}

void	exec_export(t_all *all)
{
	int		i;
	int		j;

	all->list_env->concatenate = 0;
	i = 0;
	j = 1;
	i = all->node->n_args;
	all->exit = 0;
	if (i == 1)
	{
		sort_list(&all->list_env);
		print_list(all);
	}
	else
	{
		while (all->node->args[j])
		{
			if (check_arg(all, all->node->args[j], j) == 0)
			{
				add_new(all, all->node->args[j]);
				all->list_env->concatenate = 0;
			}
			j++;
		}
	}
}
