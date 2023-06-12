/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_starts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/06/12 19:18:53 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>




#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/redirections.h"
int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes, t_cmd *temp);
int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes);
// void	execute_node(t_cmd *temp, t_all *all, t_pipe pipes);

int	is_not_forkable(char *str)
{
	if ((ft_strncmp(str, "echo", 5) == 0|| ft_strncmp(str, "cd", 3) == 0\
		|| ft_strncmp(str, "pwd", 4) == 0 || ft_strncmp(str, "export", 7) == 0 \
			|| ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "env", 4) == 0\
				|| ft_strncmp(str, "exit", 5)== 0) )
	{
			return(1);
	}
	return(0);
}


// void	single_command(t_all *all, t_cmd *temp)
// {
// 	int	stdout_copy;
// 	if (temp->redir)
// 		{
// 			stdout_copy = dup(STDOUT_FILENO);
// 			redir_loop(all->node, all);
// 			if (dup2(stdout_copy, STDOUT_FILENO) == -1) 
// 			{
// 		 		perror("dup2");
// 		 		// return 1;
//     		}
// 		}
// 		exec_cmd(all, temp);
// }

// void	multiple_commands(t_all *all)
// {
// 	int i;
// 	t_pipe pipes;
// 	t_cmd *temp;
// 	temp = all->node;

// 	i = 0;
// 	pipes.fd_temp = dup(STDIN_FILENO);
// 	while (temp)
// 	{
// 		i++;
// 		execute_node(temp, all, pipes);
// 		temp = temp->next;
// 	}
// 	// printf("soy el padre\n");
// 	while (i--)
// 		waitpid(-1, NULL, 0);
// }

// void	execute_node(t_cmd *temp, t_all *all, t_pipe pipes)
// {
// 		// t_pipe pipes;
		
// 		pipe(pipes.fd);
// 		//si falla pipe hay que liberar todo
// 		temp->pid = fork();// TODO solo se forkea en determinados casos
// 		if (temp->pid == -1)
// 		{
// 			printf("ERROR EN EL FORK\n");
// 			return ;
// 		}
// 		if (temp->pid == 0)
// 		{ 
// 			all->node = temp;//por que???????
// 			set_fd_for_pipes_child(all, &pipes, temp);
// 			// printf("entro en el hijo\n");
// 			exit (0);
// 		}
// 		set_fd_for_pipes_father( temp, &pipes);
// }

// void	minishell_starts(t_all *all)
// {
	
// 	t_cmd *temp;
// 	temp = all->node;
	
// 	if(!temp->next && is_not_forkable(temp->cmd))
// 		single_command(all, temp);
// 	else
// 		multiple_commands(all);
// }


void	minishell_starts(t_all *all)
{
	int i;
	t_pipe pipes;
	t_cmd *temp;
	int	pid_temp;
	
	temp = all->node;
	int	stdout_copy;
	i = 0;
	if(!temp->next && is_not_forkable(temp->cmd))
	{
		
		if (temp->redir)
		{
			stdout_copy = dup(STDOUT_FILENO);
			
		 	redir_loop(all->node, all);
			//caso raro 
			if (dup2(stdout_copy, STDOUT_FILENO) == -1) 
		 	{
		 		perror("dup2");
		 		// return 1;
     		}
		 }
		else
		  {
			exec_cmd(all, temp);
		  }
	}
	else
	{
		 //creamos los pipes en funcion a los nodos que tenemos
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
		 		exit (all->exit); //tiene que ser 0???
		 	}
		 	set_fd_for_pipes_father( temp, &pipes);
		 	temp = temp->next;
		 }
		//  printf("soy el padre\n");
		 while (i--)
		 	pid_temp = waitpid(-1, &all->status, 0);
		if(WIFEXITED(all->status) && pid_temp ==  lst_last(&all->node)->pid)
		{
			all->exit = WEXITSTATUS(all->status);
            // printf("Código de error del proceso hijo: %d\n", all->exit);
		}
		
		// printf("despues de todos los redireccionamientos: %d\n", all->exit);
		// printf("despues de todos los redireccionamientos: %d\n", &all->exit);
	
	}
}

