/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:45:47 by clballes          #+#    #+#             */
/*   Updated: 2023/05/19 12:59:19 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	lstfree_cmd(t_cmd **lst)
{
	t_cmd	*temp;

	while (*lst != NULL)
	{
		temp = *lst;
		while (temp != NULL)
		{
			free (temp);
			temp = temp->next;
		}
		*lst = NULL;
	}
}

void	lstfree_env(t_env **lst)
{
	t_env	*temp;

	while (*lst != NULL)
	{
		temp = *lst;
		while (temp != NULL)
		{
			free (temp);
			temp = temp->next;
		}
		*lst = NULL;
	}
}

void	free_arr(char **array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (array[len])
		len++;
	while (i < len)
	{
		free (array[i]);
		i++;
	}
	free (array);
}
