/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:25:54 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 15:27:45 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/heredoc.h"
#include "../inc/parsing.h"
#include "../inc/interactive.h"
#include "../inc/redirections.h"

// si existe y tenemos acceso, haremos el open
// file we dont have permision
// is a directory
int	access_path(char *filename, t_all *all, int *type)
{
	struct stat	info;

	if (stat(filename, &info) == 0 && *type != HDOC)
	{
		if (S_ISREG(info.st_mode))
		{
			if (access(filename, W_OK) == 0)
				return (0);
			else
				write_err(all, 1);
		}
		else
			write_err(all, 0);
	}
	else if (*type != HDOC)
	{
		if (all->node->redir->type == INPUT)
			write_err(all, 2);
		return (2);
	}
	return (0);
}

int	redir_output(t_all *all, t_redir *temp, int type)
{
	int	fd;

	fd = 0;
	if (type == 0 || type == OUT_TRUNCATED)
		fd = open(temp->file_name, O_WRONLY | O_TRUNC, 0644);
	else if (type == OUT_APPEND)
		fd = open(temp->file_name, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	if (temp->next == NULL)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		exec_cmd(all, all->node);
	}
	return (0);
}

int	redir_input(t_all *all, t_redir *temp)
{
	int	fd;

	fd = open(temp->file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open the input file\n");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	if (temp->next == NULL )
		exec_cmd(all, all->node);
	close(fd);
	return (0);
}

void	redirect(t_redir *temp, int access, t_all *all)
{
	if (access == 2 && temp->type == INPUT)
		write_err(all, 3);
	if (access == 2 && (temp->type != INPUT || temp->type != HDOC))
	{
		open(temp->file_name, O_WRONLY | O_CREAT, 0644);
		redir_output(all, temp, 0);
	}
	else
	{
		if (temp->type == OUT_TRUNCATED || temp->type == OUT_APPEND)
			redir_output(all, temp, temp->type);
		if (temp->type == INPUT)
			redir_input(all, temp);
	}
}

void	redir_loop(t_cmd **node, t_all *all)
{
	int		access;
	t_redir	*temp;

	temp = (*node)->redir;
	access = 0;
	while (temp)
	{
		access = access_path(temp->file_name, all, &temp->type);
		if (access != 1)
		{
			redirect(temp, access, all);
		}
		temp = temp->next;
	}
}
