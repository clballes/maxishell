/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:21:56 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 13:26:33 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/parsing.h"

int	check_digit_args(char **args, t_cmd *node)
{
	int	j;

	j = 0;
	while (args[1][j])
	{
		if (args[1][j] == '-' || args[1][j] == '+')
			j++;
		while (args[1][j] == ' ' && args[1][j] != '\0' && not_space(args[1]))
		{
			j++;
			if (args[1][j] == '\0')
				return (1);
		}
		if (digit_max_min(args[1][j], args[1]) == 1)
		{
			print_err("bash: exit: &: numeric argument required", node, 1);
			return (0);
		}
		else
			j++;
	}
	return (1);
}

static void	valid_arguments_exit(t_all *all, t_cmd *node)
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
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

void	exec_exit(t_all *all, t_cmd *node)
{
	if (node->empty_string)
		print_err("bash: exit: &: numeric argument required", node, 1);
	if (ft_strncmp(node->args[1], "--", 3) == 0)
	{
		all->exit = 0;
		exit(all->exit);
	}
	if (node->n_args == 1)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		exit(all->exit);
	}
	else if (check_digit_args(node->args, node) == 1 && !node->empty_string)
		valid_arguments_exit(all, node);
	else
	{
		all->exit = 255;
		exit(all->exit);
	}
}
