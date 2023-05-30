/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/05/30 17:52:38 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes);
int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes);

void	pipes(t_all *all)
{
	int i;
	t_pipe pipes;
	
	i = 0;
	//creamos los pipes en funcion a los nodos que tenemos
	pipes.fd_temp = dup(STDIN_FILENO);
	while (all->node)
	{
		pipe(pipes.fd);
		i++;
	
		// printf("inicio pipe: fd[0]:%d fd[1]:%d temp:%d\n", all->fd[0], all->fd[1], all->fd_temp);
		//si falla pipe hay que liberar todo
		all->node->pid = fork();
		if (all->node->pid == -1)
		{
			printf("ERROR EN EL FORK\n");
			return ;
		}
		if (all->node->pid == 0)
		{ 
			set_fd_for_pipes_child( all, &pipes);
			// printf("entro en el hijo\n");
			exit (0);
		}
		set_fd_for_pipes_father( all->node, &pipes);
		all->node = all->node->next;
	}
	// printf("soy el padre\n");
	while (i--)
		waitpid(-1, NULL, 0);
}

int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes)
{
	if(node->next != NULL)// nodo 1 o siguientes PADRE
	{
		close(pipes->fd_temp);
		pipes->fd_temp = pipes->fd[READ];
	}
	if(node->next == NULL)//me encuentro en el ultimo nodo PADRE
	{
		close(pipes->fd[READ]);
		close(pipes->fd_temp);
	}
	close(pipes->fd[WRITE]);
	return(0);
}

int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes)
{
	if(all->node->next != NULL)//nodo 1 o siguientes HIJO
	{
		dup2(pipes->fd[WRITE], STDOUT_FILENO);
		close(pipes->fd[READ]);
		close(pipes->fd[WRITE]);
		dup2(pipes->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		close(pipes->fd_temp);
	}
	if(all->node->next == NULL) //ultimo nodo hijo
	{
		close(pipes->fd[WRITE]);
		close(pipes->fd[READ]);
		dup2(pipes->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		close(pipes->fd_temp);
		
	}
	exec_cmd(all);
	return(0);
}