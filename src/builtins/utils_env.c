/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:50:58 by clballes          #+#    #+#             */
/*   Updated: 2023/04/27 16:51:00 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

t_env	*lst_new_env(char *name, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->content = content;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	lst_add_back_env(t_env **first, t_env *new_el)
{
	t_env	*temp;

	if (*first == NULL)
		*first = new_el;
	else
	{
		temp = lst_last_env(*first);
		temp->next = new_el;
		new_el->previous = temp;
	}
}

t_env	*lst_last_env(t_env *lst)
{
	if (lst != NULL)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}
