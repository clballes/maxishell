/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:23:05 by clballes          #+#    #+#             */
/*   Updated: 2023/05/19 19:11:20 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	swap(t_env **temp)
{
	t_env	*first;
	t_env	*second;

	first = *temp;
	second = first->next;
	if (first->next == 0)
		return ;
	first->next = second->next;
	second->previous = first->previous;
	if (first->previous)
		first->previous->next = second;
	if (second->next != 0)
		second->next->previous = first;
	second->next = first;
	first->previous = second;
}

void	change_var_list(char *content, t_env *temp)
{
	t_env	*new;

	new = temp;
	new->content = content;
}

void	sort_list(t_env **list_env)
{
	t_env	*temp;
	t_env	*temp2;

	temp = *list_env;
	temp2 = temp->next;
	while (temp && temp->next)
	{
		if (ft_strncmp(temp->name, temp2->name,
				ft_strlen(temp->name)) > 0)
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

void	print_list(t_env **list_env)
{
	t_env	*temp;

	temp = *list_env;
	while (temp)
	{
		if (temp->print == 0)
			printf("declare -x %s\n", temp->name);
		else
			printf("declare -x %s=\"%s\"\n", temp->name, temp->content);
		temp = temp->next;
	}
}
