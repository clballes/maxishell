/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:25:54 by clballes          #+#    #+#             */
/*   Updated: 2023/06/06 14:25:56 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/heredoc.h"
#include "../inc/parsing.h"
#include "../inc/interactive.h"

int	write_err(t_all *all, int j)
{
	all->exit = 1;
	if (j == 1)
		ft_putstrshell_fd("minishell: &: Permission denied", 2, all, 2);
	else if (j ==3)
		
	else
		ft_putstrshell_fd("minishell: &: Is a directory", 2, all, 2);
	write(2, "\n", 1);
	return (1);
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
			{
				write_err(all, 0); // is a directory
				exit(all->exit);
			}
		}
		else
		{
			write_err(all, 0); // is a directory
			exit(all->exit);
		}
	}
	else
		return (2);// necesitamos crear el fichero
}

int	redir_output(t_all *all, int type)
{
	int	fd;
	int	stdout_copy;

	fd = 0;
	stdout_copy = dup(STDOUT_FILENO);
	if (type == 0 || type == OUTPUT_TRUNCATED)
		fd = open(all->node->redir->file_name, O_WRONLY | O_TRUNC, 0644);
	else if (type == OUTPUT_APPEND)
		fd = open(all->node->redir->file_name, O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return 1;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return 1;
	}
	//cuando hay mas d un nodo ejecutar comadno al final
	if (all->node->redir->next == NULL)
		exec_cmd(all, all->node);
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
	int fd;
		printf("AAAAAAAAAA\n");

	fd = open(all->node->redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open the input file.\n");
		return 1;
	}
	// Redirect the standard input to the input file
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("Failed to redirect standard input.\n");
		return 1;
	}
	
	// Read input from the redirected standard input
	// char buffer[256];
	// fgets(buffer, sizeof(buffer), stdin);
	// printf("Input: %s", buffer);
	
	// Close the input file
	close(fd);
	return 0;
}

int	redir_loop(t_cmd *node, t_all *all)
{
	int	access;

	access = 0;
	while (node->redir)
	{
		printf("el redir type es %d\n", node->redir->type);
		access = access_path(node->redir->file_name, all);
		printf("el redir type es %d\n", access);
		if (access != 1)
		{
			if (access == 2 && node->redir->type == INPUT)
				write_err(all, 3);
			if (access == 2 && (node->redir->type != INPUT || node->redir->type != HEREDOC)) // fer el open idiferent de que sigui
			{
				printf("entres?\n");
				open(node->redir->file_name, O_WRONLY | O_CREAT , 0644);
				redir_output(all, 0);
			}
			else
			{
				if (node->redir->type == OUTPUT_TRUNCATED || node->redir->type == OUTPUT_APPEND)
					redir_output(all, all->node->redir->type);
				if (node->redir->type == INPUT)
				{
					printf("entru\n");
					redir_input(all);
				}
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