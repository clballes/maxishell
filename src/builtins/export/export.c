/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:09 by clballes          #+#    #+#             */
/*   Updated: 2023/04/28 12:22:13 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	print_list (t_env **list_a)
{
	t_env *temp_a;

	temp_a = *list_a;
	while (temp_a)
	{
		printf("declare -x %s=\"%s\"\n",temp_a->name, temp_a->content);
		temp_a = temp_a->next;
	}
}

void	sort_list(t_env **list_env)
{
	int		i;
	t_env	*temp;
	t_env	*temp2;
	t_env	*temp3;
	
	i = 0;
	temp3 = *list_env;
	temp = *list_env;	
	temp2 = temp->next;
	while(temp && temp->next)
	{
		if (ft_strncmp(temp->name, temp2->name, ft_strlen(temp->name)) > 0) //no estan ordenados
		{
			swap(&temp);
			if (temp2->previous == 0)
				*list_env = temp2;
			temp = *list_env;
			temp2 = temp->next;
		}
		else
		{
			temp = temp->next;
			if (temp2)
				temp2 = temp2->next;
		}
	}
}

void	exec_export(t_all *all)
{
	int	i;
	t_env	*temp;

	temp = all->list_env;
	i = 0;
	while(all->node->args[i])
		i++;
	if (i == 1)
	{
		sort_list(&all->list_env);
		print_list(&all->list_env);
	}
	else
	{
		if (check_equal(all->node) == 0)
		{
			all->list_env->temporal = lst_new_env(all->node->args[1], NULL);
			lst_add_back_env(&all->list_env, all->list_env->temporal);
			all->list_env->temporal->print = 0;
			sort_list(&all->list_env);
			print_list(&all->list_env);
		}
	}
}