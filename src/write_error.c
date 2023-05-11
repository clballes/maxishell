/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:21:56 by clballes          #+#    #+#             */
/*   Updated: 2023/05/02 10:41:26 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	ft_putcharshell_fd(char c, int fd, char **args, t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (all->node->n_args == 1)
		j = 0;
	if (c == '&')
	{
		while(args[j][i])
			write(fd, &args[j][i++], 1);
	}
	else
		write(fd, &c, 1);
}

void	ft_putstrshell_fd(char *s, int fd,  char **args, t_all *all)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putcharshell_fd(s[i], fd, args, all);
		i++;
	}
}
