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

void	swap(t_env **temp1)
{
	t_env	*first;
	t_env	*second;

	first = *temp1;
	second = first->next;
	// printf("hye1\n");
	if (first->next == 0)
		return ;
	// printf("hye2\n");
	
	first->next = second->next;
	// printf("hye3\n");
	
	second->previous = first->previous;
	// printf("el pointer es: %p\n", first->previous);
	// printf("el pointer second es: %p\n", second->previous);

	if (first->previous)
		first->previous->next = second;
	// printf("hye5\n");
	if (second->next != 0)
		second->next->previous = first;

	second->next = first;
	// printf("hye6\n");
	first->previous = second;

	// printf("hye7\n");

}
