/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/05/29 14:10:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
int	set_fd_for_pipes(t_cmd *node, t_all *all);

void	pipes(t_all *all)
{

	// printf("num pipes %d\n", all->n_pipes);
	//creamos los pipes en funcion a los nodos que tenemos
	
	while (all->node)
	{
		pipe(all->node->fd);
		//si falla pipe hay que liberar todo
		all->node->pid = fork();
		if (all->node->pid == -1)
		{
			printf("ERROR EN EL FORK\n");
			return ;
		}
		if (all->node->pid == 0)
		{ 
			printf("entro en el hijo\n");
			set_fd_for_pipes(all->node, all);
			
			exit (0); //se nos cierran los hijos pero no acaba de salir bien el prompt
		}
		printf("soy el padre\n");
	
		all->node = all->node->next;
		
	}
		close(all->node->fd[WRITE]);
	
	
		waitpid(-1, NULL, 0);
}

int	set_fd_for_pipes(t_cmd *node,t_all *all)
{
	int	fd_write;
	int	fd_read;
	int	fd_new;
	
	(void)all;
	fd_write = STDOUT_FILENO;
	fd_read = STDIN_FILENO;
	if(node->next != NULL)
	{
		close(node->fd[READ]);
		fd_write = node->fd[WRITE];
		fd_new = dup2(STDOUT_FILENO, fd_write);
		close(node->fd[WRITE]);
	}
	if(node->previous && node->next == NULL)
	{
	
		close(node->fd[WRITE]);
		fd_read = node->previous->fd[READ];
		fd_new = dup2(STDIN_FILENO, fd_read);
		close(node->fd[READ]);
	}
	
	// fd_new = dup2(fd_write, STDOUT_FILENO);
	// fd_new = dup2(fd_read, STDIN_FILENO);//protecciones de si falla
	
	
	exec_cmd(all);
	return(0);
}