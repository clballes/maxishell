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

void	exec_unset(t_all *all)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if (all->node->args[1] == NULL) //si nomes tinc larg de unset que faig
			return ;
		if (ft_strncmp(all->node->args[1],
				temp->name, ft_strlen(temp->name)) == 0)
		{
			temp->previous->next = temp->next;
			free(temp);
			return ;
		}
		else
			temp = temp->next;
	}
}
