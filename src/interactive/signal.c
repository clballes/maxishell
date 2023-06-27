/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:52:36 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 13:05:48 by albagarc         ###   ########.fr       */
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

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	handle_signals_heredoc(int sig)
{
	if (sig == SIGQUIT)
	{
		return ;
	}
	else if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "> \n", 3);
	}
}

void	init_signal(int mode,  t_all *all)
{
	struct sigaction	sa;

	(void)all;
	sa.sa_flags = SA_SIGINFO;
	if (mode == 1)
		sa.sa_handler = SIG_IGN;
	else if (mode == 2)
	{
		sa.sa_handler = &handle_signals_heredoc;
		if (sa.sa_handler)
		{
			all->exit = 1;
			all->ctrl_c = 1;
		}
	}
	else if (mode == 3)
		sa.sa_handler = &handle_signals;
	else if (mode == 0)
		sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
