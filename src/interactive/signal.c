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
		//printf("\n");
    	//rl_replace_line("", 0); // Clear input line
    	rl_on_new_line(); // Move cursor to new line
    	rl_redisplay(); // Redisplay prompt
	}
	else if (sig == SIGQUIT)
	{
		printf("holaaaa\n");
		printf("\n");
		write(STDOUT_FILENO, "exit\n",5);
		rl_on_new_line();
		rl_redisplay();
		// exit(all->exit);
	}
}
