/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:09 by clballes          #+#    #+#             */
/*   Updated: 2023/05/04 10:18:21 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "string.h"

int	ft_repeat(t_all *all, char *res, char *arg)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if ((ft_strncmp(temp->name, arg, ft_strlen(temp->name))) == 0)
		{
			if (all->list_env->concatenate == 1)
			{
				if (res == NULL)
				{
					printf("AIIII\n");
					return (1);
				}
				temp->content = ft_strjoin(temp->content, res); //ojo el
			}
			else if ((all->list_env->concatenate == 0) && (res == NULL))
				temp->print = 0;
			else if ((all->list_env->concatenate == 0) || (all->node->equal != 0))
			{
					printf("AIIII\n");
				change_var_list(res, temp);
				temp->print = 1;
			}
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	add_equal_arg(t_all *all, char *arg)
{
	char **cont_name;
	char *res;

	res = ft_strchr(arg, '=');
	res++;
	if (all->list_env->concatenate == 1)
		cont_name = ft_split(arg, '+');
	else
		cont_name = ft_split(arg, '=');
	if (ft_repeat(all, res, cont_name[0]) == 0)
	{
		all->list_env->temporal = lst_new_env(cont_name[0], res);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		all->list_env->temporal->print = 1;
	}
	free(cont_name);
}

void	add_new(t_all *all, char *arg)
{
	if (all->node->equal == 0)
	{
		if (ft_repeat(all, NULL, arg) == 1)
			return ;
		all->list_env->temporal = lst_new_env(arg, NULL);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		all->list_env->temporal->print = 0;
	}
	else
	{
		add_equal_arg(all, arg);
	}
	sort_list(&all->list_env);
}

void	exec_export(t_all *all)
{
	int		i;
	int		j;

	all->list_env->concatenate = 0;
	i = 0;
	j = 1;
	while (all->node->args[i]) //esto me lo pasara alba
		i++;
	if (i == 1)
	{
		sort_list(&all->list_env);
		print_list(&all->list_env);
	}
	else
	{
		while (all->node->args[j])
		{
			check_arg(all, all->node->args[j]); //em diu sihi han iguals
			add_new(all, all->node->args[j]);
			all->list_env->concatenate = 0;
			j++;
		}
	}
}