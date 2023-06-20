/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:52:36 by clballes          #+#    #+#             */
/*   Updated: 2023/06/15 14:45:11 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/interactive.h"

static void	handle_signals(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	set_term(t_all *all)
// {
// 	struct termios	term;
// 	(void)all;

// 	if (tcgetattr(STDIN_FILENO, &term) != 0)
// 		free_lists_and_line(all);
// 	term.c_lflag &= ~ECHOCTL;
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
// 		free_lists_and_line(all);
// }


// static void	handle_signals_heredoc(int sig)
// {
// 	if (sig == SIGQUIT)
// 		return ;
// 	else if (sig == SIGINT)
// 	{
// 		close(STDIN_FILENO);
// 		write(STDOUT_FILENO, "> \n", 3);
// 		g_glbl.g_ctrlc = 1;
// 		g_glbl.g_error = 1;
// 	}
// }

void	init_signal(int mode)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	if (mode == 1)
		sa.sa_handler = SIG_IGN; //sig ignore
	// else if (mode == 2)
	// 	sa.sa_handler = &handle_signals_heredoc;
	else if (mode == 3)
		sa.sa_handler = &handle_signals;
	else if (mode == 0)
		sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
