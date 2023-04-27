/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:30:58 by clballes          #+#    #+#             */
/*   Updated: 2023/04/25 16:58:34 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
t_cmd	*lst_new(char *line)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->line = line;
	new->next = NULL;
	return (new);
}

t_cmd	*lst_last(t_cmd *lst)
{
	if (lst != NULL)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

void	lst_add_back(t_cmd **first, t_cmd *new_el)
{
	t_cmd	*temp;

	if (*first == NULL)
		*first = new_el;
	else
	{
		temp = lst_last(*first);
		temp->next = new_el;
	}
}

t_env	*lst_new_env(char *name, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}