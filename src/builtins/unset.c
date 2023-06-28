/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:35 by clballes          #+#    #+#             */
/*   Updated: 2023/05/12 14:05:43 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	unset_if(t_env *temp, t_all *all, t_env *first)
{
	free(temp->name);
	free(temp->content);
	if (temp->previous == NULL)
	{
		temp->next->previous = NULL;
		free(temp);
		temp = temp->next;
		all->list_env = first->next;
	}
	else if (temp->next == NULL)
	{
		temp->previous->next = NULL;
		free(temp);
	}
	else
	{
		temp->previous->next = temp->next;
		temp->next->previous = temp->previous;
		free(temp);
	}
}

void	exec_unset(t_all *all)
{
	t_env	*temp;
	t_env	*first;

	first = all->list_env;
	temp = all->list_env;
	while (temp)
	{
		if (all->node->args[1] == NULL)
			return ;
		else if (ft_strncmp("_", all->node->args[1], 2) == 0)
		{
			return ;
		}
		else if (ft_strncmp(all->node->args[1],
				temp->name, ft_strlen(all->node->args[1] + 1)) == 0)
		{	
			unset_if(temp, all, first);
			return ;
		}
		else
			temp = temp->next;
	}
}
