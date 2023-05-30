/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/05/30 11:34:29 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
int	set_fd_for_pipes(t_cmd *node, t_all *all);

void	pipes(t_all *all)
{
	int i;
	i = 0;
	// printf("num pipes %d\n", all->n_pipes);
	//creamos los pipes en funcion a los nodos que tenemos
	
	pipe(all->fd);
	while (all->node)
	{
		i++;
		printf("inicio pipe: fd[0]:%d fd[1]:%d\n", all->fd[0], all->fd[1]);
		//si falla pipe hay que liberar todo
		all->node->pid = fork();
		if (all->node->pid == -1)
		{
			printf("ERROR EN EL FORK\n");
			return ;
		}
		if (all->node->pid == 0)
		{ 
			set_fd_for_pipes(all->node, all);
			printf("entro en el hijo\n");
			exit (0);
		}
		if(all->node->next == NULL)
			close(all->fd[READ]);
		close(all->fd[WRITE]);
		all->node = all->node->next;
	}
	printf("soy el padre\n");
	close(all->fd[READ]);
	while (i--)
		waitpid(-1, NULL, 0);
}

int	set_fd_for_pipes(t_cmd *node,t_all *all)
{
	if(node->next != NULL)
	{
		dup2(all->fd[WRITE], STDOUT_FILENO);
		close(all->fd[READ]);
		close(all->fd[WRITE]);
		
	}
	if(node->previous && node->next == NULL)
	{

		dup2(all->fd[READ], STDIN_FILENO);
		close(all->fd[WRITE]);
		close(all->fd[READ]);
		
	}
	exec_cmd(all);
	return(0);
}