/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/05/30 17:36:08 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
int	set_fd_for_pipes_child(t_cmd *node, t_all *all);
int	set_fd_for_pipes_father(t_all *all);

void	pipes(t_all *all)
{
	int i;
	
	i = 0;
	//creamos los pipes en funcion a los nodos que tenemos
	all->fd_temp = dup(STDIN_FILENO);
	while (all->node)
	{
		pipe(all->fd);
		i++;
		printf("inicio pipe: fd[0]:%d fd[1]:%d temp:%d\n", all->fd[0], all->fd[1], all->fd_temp);
		//si falla pipe hay que liberar todo
		all->node->pid = fork();
		if (all->node->pid == -1)
		{
			printf("ERROR EN EL FORK\n");
			return ;
		}
		if (all->node->pid == 0)
		{ 
			set_fd_for_pipes_child(all->node, all);
			// printf("entro en el hijo\n");
			exit (0);
		}
		set_fd_for_pipes_father( all);
		all->node = all->node->next;
	}
	// printf("soy el padre\n");
	while (i--)
		waitpid(-1, NULL, 0);
}

int	set_fd_for_pipes_father(t_all *all)
{
	if(all->node->next != NULL)// nodo 1 o siguientes PADRE
	{
		close(all->fd_temp);
		all->fd_temp = all->fd[READ];
	}
	if(all->node->next == NULL)//me encuentro en el ultimo nodo PADRE
	{
		close(all->fd[READ]);
		close(all->fd_temp);
	}
	close(all->fd[WRITE]);
	return(0);
}

int	set_fd_for_pipes_child(t_cmd *node,t_all *all)
{
	if(node->next != NULL)//nodo 1 o siguientes HIJO
	{
		dup2(all->fd[WRITE], STDOUT_FILENO);
		close(all->fd[READ]);
		close(all->fd[WRITE]);
		dup2(all->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		close(all->fd_temp);
	}
	if(node->next == NULL) //ultimo nodo hijo
	{
		close(all->fd[WRITE]);
		close(all->fd[READ]);
		dup2(all->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		close(all->fd_temp);
		
	}
	exec_cmd(all);
	return(0);
}