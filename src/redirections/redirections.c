/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:25:54 by clballes          #+#    #+#             */
/*   Updated: 2023/06/15 16:35:16 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/heredoc.h"
#include "../inc/parsing.h"
#include "../inc/interactive.h"
#include "../inc/redirections.h"

int	write_err(t_all *all, int j)
{
	all->exit = 1;
	if (j == 1)
		write_dyn_err("minishell: &: Permission denied", &all->node->redir->file_name[0]);
	else if (j == 2)
		write_dyn_err("minishell: &: No such file or directory", &all->node->redir->file_name[0]);
	else
		write_dyn_err("minishell: &: Is a directory", &all->node->redir->file_name[0]);
	exit(all->exit);
}

int	access_path(char *filename, t_all *all, int *type)
{
	struct stat	info;
	
	if (stat(filename, &info) == 0 && *type != HEREDOC)
	{
		if (S_ISREG(info.st_mode))
		{
			if (access(filename, W_OK) == 0)
				return (0); // si existe y tenemos acceso, haremos el open
			else
				write_err(all, 1); // file we dont have permision
		}
		else
			write_err(all, 0); // is a directory
	}
	else if (*type != HEREDOC)
	{
		if (all->node->redir->type == INPUT) // file not existent so not doing anytign in input redirection
			write_err(all, 2);
		return (2);// necesitamos crear el fichero
	}
	return (0);
}

int	redir_output(t_all *all, t_redir *temp, int type)
{
	int	fd;

	fd = 0;
	if (type == 0 || type == OUTPUT_TRUNCATED)
		fd = open(temp->file_name, O_WRONLY | O_TRUNC, 0644);
	else if (type == OUTPUT_APPEND)
		fd = open(temp->file_name, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	//cuando hay mas d un nodo ejecutar comadno al final
	// printf("cuantos nodos tiene la lista redir =%d\n",lst_size_redir(&all->node));
	if (temp->next == NULL ) //&& lst_size de t_redir es != 1)
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
	exec_cmd(all, all->node);
	// Close the input file
	close(fd);
	return (0);
}

int	redir_loop(t_cmd **node, t_all *all)
{
	int	access;
	t_redir *temp;

	temp = (*node)->redir;
	access = 0;
	while (temp)
	{
		access = access_path(temp->file_name, all, &temp->type);
		if (access != 1)
		{
			if (access == 2 && temp->type == INPUT)
				write_err(all, 3);
			if (access == 2 && (temp->type != INPUT || temp->type != HEREDOC)) // fer el open idiferent de que sigui
			{
				open(temp->file_name, O_WRONLY | O_CREAT, 0644);
				redir_output(all, temp, 0);
			}
			else
			{
				if (temp->type == OUTPUT_TRUNCATED || temp->type == OUTPUT_APPEND)
					redir_output(all, temp, temp->type);
				if (temp->type == INPUT)
					redir_input(all, temp);
			}
		}
		temp = temp->next;
	}
	return (0);
}