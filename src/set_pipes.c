/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:59:41 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/21 18:23:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/redirections.h"

int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes)
{
	if (node->next != NULL)
	{
		close(pipes->fd_temp);
		pipes->fd_temp = pipes->fd[READ];
	}
	else
	{
		close(pipes->fd_temp);
		close(pipes->fd[READ]);
	}
	close(pipes->fd[WRITE]);
	return (0);
}

//heredoce es antes de redireccionar padre hijo porque el resultado 
//del heredoc ser redirecciona al hijo
int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes, t_cmd *temp)
{
	if (temp->next != NULL)
	{
		dup2(pipes->fd_temp, STDIN_FILENO);
		dup2(pipes->fd[WRITE], STDOUT_FILENO);
		close(pipes->fd[READ]);
	}
	else
	{
		dup2(pipes->fd_temp, STDIN_FILENO);
		close(pipes->fd[WRITE]);
		close(pipes->fd[READ]);
	}
	if (temp->redir)
	{
		if (!(lst_size_redir(&temp->redir) == 1 && temp->redir->type == HDOC))
		{
			redir_loop(&all->node, all);
			return (0);
		}
	}
	// if (g_glbl.g_ctrlc == 1)
	// {
	// 	exit(1);
	// }
	exec_cmd(all, temp);
	return (0);
}
