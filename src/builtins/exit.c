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

int	check_digit_args(char **args, t_all *all)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (ft_isdigit(args[i][j]) == 0)
			{
				printf("exit\n");
				printf("bash: exit: %s: numeric argument required\n", args[i]);
				return (1);
			}
			else
				j++;
		}
		i++;
	}
	all->exit = ft_atoi(args[1]);
	all->exit = all->exit % 256;
	printf("el all exit isssss %d\n", all->exit);
	return (0);
}

int	check_num_args(int i)
{
	if (i > 2)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	else
	{
		printf("exit\n");
		return (0);
	}
}

void	exec_exit(t_all *all)
{
	int	i;

	i = 0;
	all->exit = 0;
	while (all->node->args[i])
		i++;
	if (check_digit_args(all->node->args, all) == 0)
	{
		if (check_num_args(i) == 0)
		{
			printf("el exit es %d\n", all->exit);
			exit(all->exit); //salida por el exit status
		}
		else
			return ;
	}
	else
		exit(all->exit); //numeric argument exit 2 general error
}