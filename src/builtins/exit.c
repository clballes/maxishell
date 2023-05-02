/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:21:56 by clballes          #+#    #+#             */
/*   Updated: 2023/04/28 12:21:58 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	digit_max_min(int c, char *arg)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	if (ft_strncmp(arg, "9223372036854775807", 19) > 0)
		return (0);
	if (arg[0] == '-' && (ft_strncmp(arg, "-9223372036854775807", 20) > 0))
		return (0);
	return (1);
}

int	check_num_args(int i)
{
	if (i > 2)
	{
		printf("exit\nbash: exit: too many arguments\n");
		return (1);
	}
	else
	{
		printf("exit\n");
		return (0);
	}
}

int	check_digit_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][0] == '-')
				j++;
			if (digit_max_min(args[i][j], args[i]) == 0)
			{
				if (i > 1)
					return (0);
				else
					printf("exit\nbash: exit: %s: numeric argument required\n", args[i]);
				return (1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

void	exec_exit(t_all *all)
{
	int	i;

	i = 0;
	all->exit = 0;
	all->exit = ft_atoi(all->node->args[1]);
	all->exit = all->exit % 256;
	while (all->node->args[i])
		i++;
	if (i == 1)
		exit(all->exit);
	else if (check_digit_args(all->node->args) == 0)
	{
		if (check_num_args(i) == 0)
			exit(all->exit); //salida por el exit status	
		return ;
	}
	else
		exit(all->exit); //numeric argument exit 2 general error
}