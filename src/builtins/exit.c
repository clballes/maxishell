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

void	print_err(char	**args, char *print)
{
	ft_putendl_fd("exit", 2);
	ft_putstrshell_fd(print, 2, args);
	write(1, "\n", 1);
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
	if (arg[0] == '-' && (ft_strncmp(arg, "-9223372036854775808", 0xffffff) > 0))
		return (1);
	return (0);
}

int	check_num_args(t_cmd *builtins)
{
	if (builtins->n_args > 2)
	{
		print_err(builtins->args, "bash: exit: too many arguments");
		return (1);
	}
	else
		return (0);
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
			if (args[i][j] == '-' || args[i][j] == '+')
				j++;
			if (digit_max_min(args[i][j], args[i]) == 1)
			{
				if (i > 1)
					return (1);
				else
					print_err(args, "bash: exit: &: numeric argument required");
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
	if (all->node->n_args == 1)
		exit(all->exit);
	else if (check_digit_args(all->node->args) == 1)
	{
		if (check_num_args(all->node) == 0)
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
