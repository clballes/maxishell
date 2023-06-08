/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:21:56 by clballes          #+#    #+#             */
/*   Updated: 2023/06/08 11:40:01 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	print_err(char *print, t_all *all)
{
	ft_putendl_fd("exit", 2);
	ft_putstrshell_fd(print, 2, all, 1);
	write(2, "\n", 1);
}

int	digit_max_min(int c, char *arg)
{
	int	j;

	j = 0;
	if (!(c >= '0' && c <= '9'))
		return (1);
	while (arg[j] == '0')
		j++;
	if (ft_strlen(arg + j) > 20 || (ft_strlen(arg + j) == 20 && arg[0] != '-'))
		return (1);
	if (ft_strncmp(arg, "9223372036854775807", 0xffffff) > 0)
		return (1);
	if ((arg[0] == '-')
		&& (ft_strncmp(arg, "-9223372036854775808", 0xffffff) > 0))
		return (1);
	return (0);
}

int	check_num_args(t_all *all)
{
	// lst_last(&all->node)->n_args
	if (all->node->n_args > 2)
	{
		print_err("bash: exit: too many arguments", all);
		return (1);
	}
	else
		return (0);
}

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
			if (args[i][j] == '-' || args[i][j] == '+')
				j++;
			if (digit_max_min(args[i][j], args[i]) == 1)
			{
				if (i > 1)
					return (1);
				else
					print_err("bash: exit: &: numeric argument required", all);
				return (0);
			}
			else
				j++;
		}
		i++;
	}
	return (1);
}

void	exec_exit(t_all *all)
{
	// printf("num args %d\n", lst_last(&all->node)->n_args);
	if (all->node->n_args == 1)
		exit(all->exit);
	else if (check_digit_args(all->node->args, all) == 1)
	{
		if (check_num_args(all) == 0)
		{
			all->exit = ft_atoi(all->node->args[1]);
			all->exit = all->exit % 256;
			exit(all->exit);
		}
		else
		{
			all->exit = 1;
			return ;
		}
	}
	else //unsigned int y luego a int
	{
		all->exit = 255;
		exit(all->exit);
	}
}
