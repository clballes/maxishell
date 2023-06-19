/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:21:56 by clballes          #+#    #+#             */
/*   Updated: 2023/06/19 15:46:43 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/parsing.h"

void	print_err(char *print, t_cmd *node)
{
	ft_putendl_fd("exit", 2);
	write_dyn_err(print, node->args[1]);
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

int	check_num_args(t_cmd *node)
{
	if (node->n_args > 2)
	{
		print_err("bash: exit: too many arguments", node);
		return (1);
	}
	else
		return (0);
}

int	not_space(char *args)
{
	int	i;
	i = 0;
	while (args[i])
	{
		if (!ft_is_space(args[i]))
			return(1);
		i++;
	}
	return(0);
	
}
int	check_digit_args(char **args, t_cmd *node)
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
			while(args[i][j] == ' ' && args[i][j] != '\0' && not_space(args[i]))
			{
				j++;
				if (args[i][j] == '\0')
					return (1);
					
			}
				//hay que tener en cuenta los espacios
			if (digit_max_min(args[i][j], args[i]) == 1 )
			{
				if (i > 1)
					return (1);
				else
					print_err("bash: exit: &: numeric argument required", node);
				return (0);
			}
			else 
				j++;
		}
		i++;
	}
	return (1);
}

void	exec_exit(t_all *all, t_cmd *node)
{
	
	if (node->empty_string)
		print_err("bash: exit: &: numeric argument required", node);
	if (node->n_args == 1)
		exit(all->exit);
	else if (check_digit_args(node->args, node) == 1 && !node->empty_string)
	{
		if (check_num_args(node) == 0)
		{
			all->exit = ft_atoi(node->args[1]);
			all->exit = all->exit % 256;
			exit(all->exit);
		}
		else
		{
			all->exit = 1;
			return ;
		}
	}
	else
	{
		all->exit = 255;
		exit(all->exit);
	}
}
