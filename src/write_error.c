/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:21:56 by clballes          #+#    #+#             */
/*   Updated: 2023/05/02 10:41:26 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	write_dyn_err(char *message, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (message[i])
	{
		if (message[i] == '&')
		{
			while(var[j])
				write(2, &var[j++], 1);
			i++;
		}
		else
			write(2, &message[i++], 1);
	}
	write(2, "\n", 1);
}