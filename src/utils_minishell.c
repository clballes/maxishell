/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:30:58 by clballes          #+#    #+#             */
/*   Updated: 2023/05/19 13:11:02 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// t_cmd	*lst_new(char *line)
// {
// 	t_cmd	*new;

// 	new = ft_calloc(1, sizeof(t_cmd));
// 	if (!new)
// 		return (0);
// 	new->line = line;
// 	new->next = NULL;
// 	return (new);
// }

t_cmd	*lst_new(char *line)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (0);
	new->line = line;
	new->next = NULL;
	return (new);
}

t_cmd	*lst_last(t_cmd **lst)
{
	t_cmd	*temp;

	temp = *lst;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
	}
	return (temp);
}

void	lst_add_back(t_cmd **first, t_cmd *new_el)
{
	t_cmd	*temp;

	if (*first == NULL)
		*first = new_el;
	else
	{
		temp = lst_last(first);
		temp->next = new_el;
	}
}

int	lst_size(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
