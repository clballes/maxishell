/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:50:58 by clballes          #+#    #+#             */
/*   Updated: 2023/06/08 15:00:35 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

t_env	*lst_new_env(char *name, char *content)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		// lstfree_env()
		return (0);
	}
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

int	lst_size_env(t_env **lst)
{
	int i;
	t_env *temp;
	
	i = 0;
	temp = *lst;
	while(temp)
	{
		temp = temp->next;
		i++;
	}
	return(i);
}