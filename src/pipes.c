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
	pid_t *pid;
	int	i;
	int n_pipes;

	n_pipes = all->n_pipes;
	pid = ft_calloc(n_pipes + 1, sizeof(pid_t));
	i = 0;
	// printf("num pipes %d\n", all->n_pipes);
	//creamos los pipes en funcion de npipes que tengamos
	while (n_pipes)
	{
		pipe(all->node[i].fd);
		//si falla pipe hay que 
		i++;
		n_pipes--;
	}
	i = 0;
	//ahora creamos los processos con el fork
	while (i <= all->n_pipes)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			printf("ERROR EN EL FORK\n");
			return ;
		}
		if (pid[i] == 0)
		{
			// printf("num pipes %d\n", all->n_pipes);
			int j;
			j = 0;
			while (j < all->n_pipes + 1)
			{
				printf("LA I ES %d\n", i);
				if (i == 0)
				{
					printf("estoy en el primer if\n");
					dup2(all->node[j].fd[1], STDOUT_FILENO);
				}
				else if(i == all->n_pipes)
				{
					printf("estoy en el segundp if\n");
					dup2(all->node[j].fd[0], STDIN_FILENO);
				}
				else
				{
					printf("estoy en el tercer if\n");
					dup2(all->node[j].fd[0], STDIN_FILENO);
					dup2(all->node[j + 1].fd[1], STDOUT_FILENO);
				}
				if (i != j)
				{
					printf("entro en el primer i != j\n");
					close(all->node[j].fd[0]);
					close(all->node[0].fd[0]);
				}
				if (i + 1 != j)
				{
					printf("entro en el segundo i + 1 != j \n");
					close(all->node[j].fd[1]);
					close(all->node[1].fd[1]);
				}
				j++;
				exit (0); //se nos cierran los hijos pero no acaba de salir bien el prompt
			}
		}
		exec_cmd(all);
		close(all->node[i].fd[0]);
        close(all->node[i + 1].fd[1]);
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

		// int x;
        //     if (read(all->node[i].fd[0], &x, sizeof(int)) == -1) {
        //         printf("Error at reading\n");
        //         return ;
        //     }
        //     printf("(%d) Got %d\n", i, x);
        //     x++;
        //     if (write(all->node[i + 1].fd[1], &x, sizeof(int)) == -1) {
        //         printf("Error at writing\n");
        //         return ;
        //     }
