/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:26:39 by clballes          #+#    #+#             */
/*   Updated: 2023/06/21 18:28:34 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	is_there_heredoc(t_redir **redir)
{
	t_redir	*temp;

	temp = *redir;
	while (temp)
	{
		if (temp->type == 4)
			return (1);
		temp = temp->next;
	}
	return (0);
}

// check line for heredoc
void	heredoc(t_all *all, char *delimitator, int *fd_temp)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
	{
		ft_putstr_fd("There was an error creating the pipe\n", 2);
		free_lists_and_line(all);
	}
	init_signal(2, all);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimitator, (ft_strlen(delimitator) + 1)) != 0)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		else
			break ;
		free(line);
	}
	dup2(fd[0], *fd_temp);
	free(line);
	close(fd[1]);
	if (g_glbl.g_ctrlc == 1)
	{
		exit(1);
	}
}

void	heredoc_fork(t_cmd *temp, t_all *all, t_pipe *pipes)
{
	temp->pid = fork();
	if (temp->pid == -1)
	{
		ft_putstr_fd("There was an error while creating a child with fork\n", 2);
		free_lists_and_line(all);
	}
	if (temp->pid == 0)
	{
		heredoc(all, temp->redir->file_name, &pipes->fd_temp);
		// if (g_glbl.g_ctrlc == 1)
		// {
		// 	exit(1);
		// }
		exit(all->exit);
	}
	init_signal(1, all);
	temp->pid = waitpid(-1, &all->status, 0);
}