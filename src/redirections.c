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
void	access_path(t_all *all) //li passem el filename
{
	const char *name = "myfile.txt";
	struct stat info;

    if (stat(name, &info) == 0) {
        if (S_ISREG(info.st_mode)) {
			//si ja existeix el file > hem de sobreesciure
			// si es laltre hem de fer el append
            printf("%s is a regular file.\n", name);
        } else {
			//tirar error de es un directorio o el q sigui
            printf("%s exists, but it is not a regular file.\n", name);
        }
    } else {
		// funcion de access permisos
		// if (si es append o truncate)
		// redir(all);
		//fer el open i afegir la info ens dona igual qun metode seguir
        printf("%s does not exist or cannot be accessed.\n", name);
    }
}

int	redir_truncate(t_all *all)
{
	// if (o_truncate)
	access_path(all);
   	int fd = open(all->node->args[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // int fd = open(all->node->redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
	{
        perror("open");
        return 1;
    }
    // Save the current standard output
    int stdout_copy = dup(STDOUT_FILENO);
	// printf("el in es %d\n", stdout_copy);
    // Redirect the standard output to the file
    if (dup2(fd, STDOUT_FILENO) == -1)
	{
        perror("dup2");
        return 1;
    }
    // Execute the command
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

//funcion para hacer <
// int	redir_append(t_all *all)
// {





// }
//funcion para hacer >>
//funcion para hacer << HEREDOC
