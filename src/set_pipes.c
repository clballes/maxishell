/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:59:41 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/12 19:17:37 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/redirections.h"

int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes)
{
	if(node->next != NULL)// nodo 1 o siguientes del PADRE
	{
		close(pipes->fd_temp);
		pipes->fd_temp = pipes->fd[READ];
	}
	else//me encuentro en el ultimo nodo del PADRE
	{
		close(pipes->fd_temp);
		close(pipes->fd[READ]);
	}
	close(pipes->fd[WRITE]);
	return(0);
}

int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes, t_cmd *temp)
{
	if (temp->next != NULL)//nodo 1 o siguientes del HIJO
	{
		dup2(pipes->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		dup2(pipes->fd[WRITE], STDOUT_FILENO);
		close(pipes->fd[READ]);
	}
	else//ultimo nodo hijo
	{
		dup2(pipes->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		close(pipes->fd[WRITE]);
		close(pipes->fd[READ]);
	}
	if (temp->redir)
	{
		redir_loop(all->node, all);
		return (0);
	}
	exec_cmd(all, temp);
	return(0);
}