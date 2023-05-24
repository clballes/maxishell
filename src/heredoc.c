/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:26:39 by clballes          #+#    #+#             */
/*   Updated: 2023/05/24 10:26:40 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	heredoc(t_all *all)
{
	int	i;

	i = 0;
	while (all->node->args[i])
	{
		if ((ft_strncmp(all->node->args[i], "<<", ft_strlen(all->node->args[i])) == 0)) //si trobem la direccio
			printf("args son %s\n", all->node->args[i]);
		printf("all->node cmd %s\n", all->node->cmd);
		i++;
	}
}