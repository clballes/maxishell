/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:52:36 by clballes          #+#    #+#             */
/*   Updated: 2023/05/12 13:52:40 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/interactive.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT) //retorn siginit el valor de ctrt c, que hy de fer un new prompt
	{
		// get_line();
		printf("holaaaaaa guapi\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("holaaaaaa\n");
		exit(0);
	}
}
