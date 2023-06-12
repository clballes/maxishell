/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:25:54 by clballes          #+#    #+#             */
/*   Updated: 2023/06/12 20:46:06 by albagarc         ###   ########.fr       */
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
		ft_putstrshell_fd("minishell: &: Permission denied", 2, all, 2);
	else if (j == 2)
		ft_putstrshell_fd("minishell: &: No such file or directory", 2, all, 2);
	else
		ft_putstrshell_fd("minishell: &: Is a directory", 2, all, 2);
	write(2, "\n", 1);
	exit(all->exit);
}

int	access_path(char *filename, t_all *all)
{
	struct stat	info;

	if (stat(filename, &info) == 0)
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
	else
	{
		if (all->node->redir->type == INPUT) // file not existent so not doing anytign in input redirection
			write_err(all, 2);
		return (2);// necesitamos crear el fichero
	}
	return (0);
}

int	redir_output(t_all *all, int type)
{
	int	fd;
	// int	stdout_copy;

	fd = 0;
	// stdout_copy = dup(STDOUT_FILENO);
	if (type == 0 || type == OUTPUT_TRUNCATED)
		fd = open(all->node->redir->file_name, O_WRONLY | O_TRUNC, 0644);
	else if (type == OUTPUT_APPEND)
		fd = open(all->node->redir->file_name, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	// if (dup2(fd, STDOUT_FILENO) == -1)
	// {
	// 	perror("dup2");
	// 	return (1);
	// }
	//cuando hay mas d un nodo ejecutar comadno al final
	// printf("cuantos nodos tiene la lista redir =%d\n",lst_size_redir(&all->node->redir));
	if (all->node->redir->next == NULL ) //&& lst_size de t_redir es != 1)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				return (1);
			}
			exec_cmd(all, all->node);
			
		}
	// if (dup2(stdout_copy, STDOUT_FILENO) == -1) esto lo hemos de hacer si no es forkabloe TODO
	// {
	//	 perror("dup2");
	//	 return 1;
    // }
    // if (close(fd) == -1) {
    //     perror("close");
    //     return 1;
    // }
	return (0);
}

int	redir_input(t_all *all)
{
	int	fd;

	fd = open(all->node->redir->file_name, O_RDONLY);
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

int	redir_loop(t_cmd *node, t_all *all)
{
	int	access;

	access = 0;
	while (node->redir)
	{
		access = access_path(node->redir->file_name, all);
		if (access != 1)
		{
			if (access == 2 && node->redir->type == INPUT)
				write_err(all, 3);
			if (access == 2 && (node->redir->type != INPUT || node->redir->type != HEREDOC)) // fer el open idiferent de que sigui
			{
				open(node->redir->file_name, O_WRONLY | O_CREAT, 0644);
				redir_output(all, 0);
			}
			else
			{
				if (node->redir->type == OUTPUT_TRUNCATED || node->redir->type == OUTPUT_APPEND)
					redir_output(all, all->node->redir->type);
				if (node->redir->type == INPUT)
					redir_input(all);
				if (node->redir->type == HEREDOC)
					printf("hola5");
			}
		}
		// else
		// 	liberar todo
		// 	salir del bucle
		node->redir = node->redir->next;
	}
	return (0);
}