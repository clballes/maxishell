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
            printf("%s is a regular file.\n", filename);
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
        printf("%s does not exist or cannot be accessed.\n", filename);
		return(2);
    }
}

int	redir_truncate(t_all *all)
{
	printf("el filename es %s\n", all->node->redir->file_name);
    int fd = open(all->node->redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	//cuando hay mas d un nodo
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

int	redir_bucle(t_cmd *node)
{
	while(node->redir)
	{
		if(access_path(node->redir->file_name) != 1)
		{
			if (access_path(node->redir->file_name) == 2)
			{
				open(node->redir->file_name, O_WRONLY | O_CREAT , 0644);
				//llamar a truncate
			}
			else
			{
				if (node->redir->type == OUTPUT_TRUNCATED)
				{
					redir_truncate();
				}
				if (node->redir->type == OUTPUT_APPEND)
				if (node->redir->type == INPUT)
				if (node->redir->type == HEREDOC)

			}
		}
		// else
		// 	liberar todo
		// 	salir del bucle
		node->redir = node->redir->next;
	}
}
//funcion para hacer >>
//funcion para hacer << HEREDOC
