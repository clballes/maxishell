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
int	redir_truncate(t_all *all)
{
    int fd = open(all->node->args[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // int fd = open(all->node->redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("el fd es : %d\n", fd);
    if (fd == -1)
	{
        perror("open");
        return 1;
    }
    // Save the current standard output
    int stdout_copy = dup(STDOUT_FILENO);
	printf("el in es %d\n", stdout_copy);
    // Redirect the standard output to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }
    // Execute the command
	exec_cmd(all);
    // Restore the standard output
    if (dup2(stdout_copy, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }
    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }
    return 0;
}

//funcion para hacer <
//funcion para hacer >>
//funcion para hacer << HEREDOC
