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

int	check_digit_args(char **args, t_cmd *builtins)
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
	builtins->exit = ft_atoi(args[1]);
	if (builtins->exit > 255)
		builtins->exit = 0;
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

void	exec_exit(t_cmd *builtins)
{
	int	i;

	i = 0;
	builtins->exit = 0;
	while (builtins->args[i])
		i++;
	if (check_digit_args(builtins->args, builtins) == 0)
	{
		if (check_num_args(i) == 0)
		{
			printf("el exit es %d\n", builtins->exit);
			exit(builtins->exit); //salida por el exit status
		}
		else
			return ;
	}
	else
		exit(0); //numeric argument exit 2 general error
}
