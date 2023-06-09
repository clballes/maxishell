/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_starts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/06/09 16:15:39 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/redirections.h"
int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes, t_cmd *temp);
int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes);

int	is_not_forkable(char *str)
{
	if ((ft_strncmp(str, "echo", 5) == 0|| ft_strncmp(str, "cd", 3) == 0\
		|| ft_strncmp(str, "pwd", 4) == 0 || ft_strncmp(str, "export", 7) == 0 \
			|| ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "env", 4) == 0\
				|| ft_strncmp(str, "exit", 5)== 0) )
	{
		printf("entro\n");
			return(1);
	}
	return(0);
}


void	single_command(t_all *all, t_cmd *temp)
{
	int	stdout_copy;
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

void	multiple_commands(t_all *all)
{
	int i;
	t_pipe pipes;
	t_cmd *temp;
	temp = all->node;

	i = 0;
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
void	minishell_starts(t_all *all)
{
	
	t_cmd *temp;
	temp = all->node;
	
	if(!temp->next && is_not_forkable(temp->cmd))
	{
		single_command(all, temp);
	}
	else
	{
		
		multiple_commands(all);
	}
}

