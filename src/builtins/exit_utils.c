/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:12:24 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/22 16:26:48 by albagarc         ###   ########.fr       */
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
			return (1);
		i++;
	}
	return (0);
}
