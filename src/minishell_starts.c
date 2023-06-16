/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_starts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:10:16 by clballes          #+#    #+#             */
/*   Updated: 2023/06/16 15:38:51 by albagarc         ###   ########.fr       */
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
#include "../inc/heredoc.h"

int	set_fd_for_pipes_child(t_all *all, t_pipe *pipes, t_cmd *temp);
int	set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes);
int	is_there_heredoc(t_redir **redir);
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


void	single_command_no_fork(t_all *all, t_cmd *temp, t_pipe *pipes)
{
	int	stdout_copy;
	
	pipes->fd_temp = dup(STDIN_FILENO);
	if(is_there_heredoc(&temp->redir))
		heredoc(all, temp->redir->file_name, &pipes->fd_temp);
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
	else
		exec_cmd(all, temp);
}

void	multi_command_or_fork(t_cmd *temp, t_pipe *pipes, t_all *all)
{
	if(is_there_heredoc(&temp->redir))
		heredoc(all, temp->redir->file_name, &pipes->fd_temp);
	pipe(pipes->fd);
	
	//si falla pipe hay que liberar todo
	temp->pid = fork();
	if (temp->pid == -1)
	{
		printf("ERROR EN EL FORK\n");
		return ;
	}
	if (temp->pid == 0)
	{ 
		all->node = temp;	
		set_fd_for_pipes_child(all, pipes, temp);
		exit (all->exit); 
	}
	set_fd_for_pipes_father(temp, pipes);
}

void	minishell_starts(t_all *all)
{
	int i;
	t_pipe pipes;
	t_cmd *temp;
	int	pid_temp;
	
	temp = all->node;
	i = 0;
	if(!temp->next && is_not_forkable(temp->cmd))
		single_command_no_fork(all, temp, &pipes);
	else
	{
		pipes.fd_temp = dup(STDIN_FILENO);
		while (temp)
		{
			i++;
			multi_command_or_fork(temp, &pipes, all);
			temp = temp->next;
		}
		while (i--)
			pid_temp = waitpid(-1, &all->status, 0);
		if(WIFEXITED(all->status) && pid_temp ==  lst_last(&all->node)->pid)
			all->exit = WEXITSTATUS(all->status);
	}
}

int	is_there_heredoc(t_redir **redir)
{
	t_redir *temp;

	temp = *redir;
	while(temp)
	{
		if(temp->type == 4)
			return(1);
		temp = temp->next;
	}
	return(0);
}