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

int	access_path(char *filename)
{
	struct stat info;

    if (stat(filename, &info) == 0)
	{
        if (S_ISREG(info.st_mode))
		{
			if (access(filename, R_OK | W_OK | X_OK) == 0) //modes del file ne el acess R - read W - write - Execute
			{
            	printf("%s FILE EXISTS AND IT is a regular file with all permision guaranteed \n", filename);
				return(0);
			}
			else
			{
				// all->exit = 1
				// bash: readme.md: Permission denied
				ft_putstrshell_fd("minishell: &: command not found", 2, all, 0);
				write(2, "\n", 1);
				return (1);
			}
        }
		else
		{
			// all->exit = 1;
            // printf("%s exists, but it is not a regular file.\n", filename);
			ft_putstrshell_fd("minishell: &: Is a directory", 2, all, 0);
			write(2, "\n", 1);
			return(1);
        }
    } else {

        printf("%s does not exist, so we need to create ---- \n", filename);
		return(2);
    }
}

int	redir_truncate(t_all *all, int type)
{
	int fd;

	fd = 0;
	if (type == '\0' || type == OUTPUT_TRUNCATED)
    	fd = open(all->node->redir->file_name, O_WRONLY | O_TRUNC, 0644);
	else if (type == OUTPUT_APPEND)
	{
		printf("entruuuuuu\n");
    	fd = open(all->node->redir->file_name, O_WRONLY | O_APPEND, 0644);
	}
    if (fd == -1)
	{
        perror("open");
        return 1;
    }
    int stdout_copy = dup(STDOUT_FILENO);
    if (dup2(fd, STDOUT_FILENO) == -1)
	{
        perror("dup2");
        return 1;
    }
	//cuando hay mas d un nodo ejecutar comadno al final
	if (all->node->redir->next == NULL)
		exec_cmd(all);
    if (dup2(stdout_copy, STDOUT_FILENO) == -1)
	{
        perror("dup2");
        return 1;
    }
    // if (close(fd) == -1) {
    //     perror("close");
    //     return 1;
    // }
    return 0;
}

int	redir_bucle(t_cmd *node, t_all *all)
{
	int access;

	access = 0;
	while (node->redir)
	{
		access = access_path(node->redir->file_name);
		if (access != 1)
		{
			if (access == 2)
			{
				open(node->redir->file_name, O_WRONLY | O_CREAT , 0644);
				redir_truncate(all, '\0');
			}
			else
			{
				if (node->redir->type == OUTPUT_TRUNCATED || node->redir->type == OUTPUT_APPEND )
					redir_truncate(all, all->node->redir->type);
				if (node->redir->type == INPUT)
					printf("hola4");
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


//funcion para hacer >>
//funcion para hacer << HEREDOC
