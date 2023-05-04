/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:23:05 by clballes          #+#    #+#             */
/*   Updated: 2023/05/04 10:20:15 by clballes         ###   ########.fr       */
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

int	ft_prohibited(char c, int j, int flag, int concat)
{
	if (c == '=')
		return (0);
	if ((j == 0) && (concat == 0) && (flag == 0) && ((c >= 33 && c <= 64)
			|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126)))
		return (1);
	// else if(concat == 1)
	// 	return (0)
	else if ((j != 0) && (flag == 0) && (concat == 0) && ((c >= 34 && c <= 47)
			|| (c >= 58 && c <= 64) || (c >= 91 && c <= 96)
			|| (c >= 123 && c <= 126)))
		return (1);
	else if ((flag == 1) && (j != 0) && (concat == 1))
		return (0);
	return (0);
}
