/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/06/01 16:05:37 by albagarc         ###   ########.fr       */
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
		if (all->node->redir)
			redir_bucle(all);
		pipe(pipes.fd);
		i++;

		// printf("inicio pipe: fd[0]:%d fd[1]:%d temp:%d\n", pipes.fd[0], pipes.fd[1], pipes.fd_temp);
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

int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes)
{
	if(all->node->next != NULL)//nodo 1 o siguientes del HIJO
	{
		//El dup2 cierra el filedescriptor viejo;
		dup2(pipes->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		dup2(pipes->fd[WRITE], STDOUT_FILENO);
		close(pipes->fd[READ]);
		
		// if(close(pipes->fd[WRITE]) == -1)
			// fprintf(stderr, "hola\n");
		// close(pipes->fd_temp);
	}
	else//ultimo nodo hijo
	{
		dup2(pipes->fd_temp, STDIN_FILENO);//lo que tengo en fd lo pongo en STDIN
		close(pipes->fd[WRITE]);
		close(pipes->fd[READ]);
		// close(pipes->fd_temp);
		
	}
	exec_cmd(all);
	return(0);
}