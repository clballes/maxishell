/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_starts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/06/09 15:38:12 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/redirections.h"
int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes, t_cmd *temp);
int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes);

int	is_not_forkable(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0|| ft_strncmp(str, "cd", 3) == 0\
		|| ft_strncmp(str, "pwd", 4) == 0 || ft_strncmp(str, "export", 7) == 0 \
			|| ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "env", 4) == 0\
				|| ft_strncmp(str, "exit", 5) == 0)
	
	{
			return(1);
	}
	return(0);
}
void	minishell_starts(t_all *all)
{
	int i;
	t_pipe pipes;
	t_cmd *temp;
	temp = all->node;
	int	stdout_copy;
	i = 0;
	// //creamos los pipes en funcion a los nodos que tenemos
	if(!temp->next && is_not_forkable(temp->cmd))
	{
		if (temp->redir)
		{
			stdout_copy = dup(STDOUT_FILENO);
			redir_loop(all->node, all);
			if (dup2(stdout_copy, STDOUT_FILENO) == -1) 
			{
		 		perror("dup2");
		 		// return 1;
    		}
		}
		exec_cmd(all, temp);
	}
	// {
	// 	// REDIR export hola=hola > x
	// 	// EXEC - cd env export unset exit
	// 	return ;
	// }
	else
	{
		pipes.fd_temp = dup(STDIN_FILENO);
		while (temp)
		{
			
			pipe(pipes.fd);
			i++;
			//si falla pipe hay que liberar todo
			temp->pid = fork();// TODO solo se forkea en determinados casos
			if (temp->pid == -1)
			{
				printf("ERROR EN EL FORK\n");
				return ;
			}
			if (temp->pid == 0)
			{ 
				all->node = temp;
				set_fd_for_pipes_child( all, &pipes, temp);
		
				// printf("entro en el hijo\n");
				exit (0);
			}
			set_fd_for_pipes_father( temp, &pipes);
			temp = temp->next;
		}
		// printf("soy el padre\n");
		while (i--)
			waitpid(-1, NULL, 0);
	}
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
		return 0;
	}
	exec_cmd(all, temp);
	return(0);
}