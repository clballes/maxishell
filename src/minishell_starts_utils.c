/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_starts_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:37:20 by clballes          #+#    #+#             */
/*   Updated: 2023/06/28 17:43:46 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/redirections.h"

void	have_redirections(t_all *all)
{
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	redir_loop(&all->node, all);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_lists_and_line(all);
	}
}
