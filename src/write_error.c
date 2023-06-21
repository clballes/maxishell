/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:21:56 by clballes          #+#    #+#             */
/*   Updated: 2023/06/21 18:23:58 by albagarc         ###   ########.fr       */
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
			while (var[j])
				write(2, &var[j++], 1);
			i++;
		}
		else
			write(2, &message[i++], 1);
	}
	write(2, "\n", 1);
}
