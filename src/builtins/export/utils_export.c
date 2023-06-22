/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:23:05 by clballes          #+#    #+#             */
/*   Updated: 2023/06/22 17:01:55 by albagarc         ###   ########.fr       */
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

	if(content == NULL)
		content = ft_strdup("");
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

void	print_list(t_all *all)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if ((ft_strncmp(temp->name, "_", ft_strlen(temp->name)) == 0)
			&& (ft_strncmp(temp->content, \
			"/usr/bin/env", ft_strlen(temp->content)) == 0))
		{
			if (temp->next == NULL)
				break ;
			temp = temp->next;
		}
		if (temp->print == 0 || (all->cd == 0
				&& (ft_strncmp(temp->name, "OLDPWD",
						ft_strlen(temp->name)) == 0)))
			printf("declare -x %s\n", temp->name);
		else
		{
			if (temp->content == NULL)
				printf("declare -x %s=\"\"\n", temp->name);
			else
				printf("declare -x %s=\"%s\"\n", temp->name, temp->content);
		}
		temp = temp->next;
	}
}
