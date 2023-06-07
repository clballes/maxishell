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

//funcion para hacer '>' esto es 0_TRUNCATE
int	access_path(char *filename) //li passem el filename
{
	struct stat info;

    if (stat(filename, &info) == 0)
	{
        if (S_ISREG(info.st_mode)) {
			//si ja existeix el file > hem de sobreesciure
			// si es laltre hem de fer el append
            printf("%s FILE EXISTS AND IT is a regular file.\n", filename);
			return(0);
        } else {
			// all->exit = 1;
			//tirar error de es un directorio o el q sigui
            printf("%s exists, but it is not a regular file.\n", filename);
			return(1);
        }
    } else {
		// funcion de access permisos
		// if (si es append o truncate)
		// redir(all);
		//fer el open i afegir la info ens dona igual qun metode seguir
		// if(access not permited)
		// 	return(1);
        printf("%s does not exist, so we need to create ---- \n", filename);
		return(2);
    }
}

int	redir_truncate(t_all *all, int type)
{
	int fd;
	fd = 0;
	// printf("holaaaa que tal entru\n");
	// printf("el filename es %s\n", all->node->redir->file_name);
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
	//cuando hay mas d un nodo ejecutar comadno
	exec_cmd(all);
    // Restore the standard output
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
	while(node->redir)
	{
		access = access_path(node->redir->file_name);
		if(access != 1)
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
