/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/05/26 11:10:17 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"


void	pipes(t_all *all)
{

	// printf("num pipes %d\n", all->n_pipes);
	//creamos los pipes en funcion a los nodos que tenemos
	while (all->node)
	{
		pipe(node->fd);
		//si falla pipe hay que liberar todo
		all->node->pid = fork();
		if (pid[i] == -1)
		{
			printf("ERROR EN EL FORK\n");
			return ;
		}
		if (pid[i] == 0)
		{
			set_fd_for_pipes(node, all);
		
				exit (0); //se nos cierran los hijos pero no acaba de salir bien el prompt
		}
		exec_cmd(all);
		close(all->node[i].fd[0]);
        close(all->node[i + 1].fd[1]);
		waitpid(pid[i], NULL, 0);
		i++;
		
	}
}

int	set_fd_for_pipes(t_cmd *node, t_all *all)
{
	
}		