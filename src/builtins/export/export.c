/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:09 by clballes          #+#    #+#             */
/*   Updated: 2023/05/22 15:49:13 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	ft_repeat(t_all *all, char *res, char *arg)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if ((ft_strncmp(temp->name, arg, ft_strlen(arg) + 1)) == 0) 
		{
			if (all->list_env->concatenate == 1)
				temp->content = ft_strjoin(temp->content, res, 0, 0); //ojo el
			else if ((all->list_env->concatenate == 0) && (res == NULL))
			{
				if (temp->content) //si printejem hola=a i despres, hola, necessito q ess qedi el valor atnerior
					temp->print = 1;		
				else
					temp->print = 0; 
			}
			else if ((all->list_env->concatenate == 0)
				|| (all->node->equal != 0))
			{
				change_var_list(res, temp);
				temp->print = 1;
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

	name = extract_var_name(arg);
	name_value = extract_var_value(arg);
	if (ft_repeat(all, name_value, name) == 1)
		return ;
	if (ft_repeat(all, name_value, name) == 0)
	{
		all->list_env->temporal = lst_new_env(name, name_value);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		if (name_value == NULL)
			all->list_env->temporal->print = 0;
		else
			all->list_env->temporal->print = 1;
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
