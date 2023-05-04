/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:23:05 by clballes          #+#    #+#             */
/*   Updated: 2023/04/28 12:23:06 by clballes         ###   ########.fr       */
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

int	ft_prohibited(char c, int j)
{
	if ((j == 0) && ((c >= 33 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)))
		return (1);
	else if ((j != 0) && ((c >= 34 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)))
		return (1);
	return (0);
}