/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:07:21 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 13:02:52 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	check_arg(t_all *all, char *arg, int j)
{
	int	i;

	all->node->equal = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			all->list_env->concatenate = 1;
		if (arg[i] == '=')
			all->node->equal = 1;
		if (ft_prohibited(arg[i], i, all->node->equal,
				all->list_env->concatenate) == 1)
		{
			all->exit = 1;
			write_dyn_err("bash: export: `&': not a valid identifier", \
			all->node->args[j]);
			return (1);
		}
		else
			i++;
	}
	return (0);
}

int	ft_prohibited(char c, int index, int equal, int concat)
{
	if (c == '=' && (index != 0))
		return (0);
	else if ((index == 0) && (!(ft_isalpha(c))))
		return (1);
	else if ((index != 0) && (equal == 0)
		&& (concat == 0) && ((c >= 32 && c <= 47)
			|| (c >= 58 && c <= 64) || (c >= 91 && c <= 94)
			|| (c >= 123 && c <= 126)))
		return (1);
	else if ((equal == 1) && (index != 0) && (concat == 1))
		return (0);
	return (0);
}

char	*extract_var_value(char *arg)
{
	char	*var_value;
	int		i;

	i = 0;
	while (*arg != '=' && *arg != '+' && *arg != '\0')
		arg++;
	if (*arg == '+')
		arg++;
	if (*arg == '=')
		arg++;
	if (*arg == '\0')
		return (NULL);
	while (arg[i] != '=' && arg[i] != '+' && arg[i] != '\0')
		i++;
	var_value = malloc(sizeof(char) * i + 1);
	i = 0;
	while (arg[i] != '\0')
	{
		var_value[i] = arg[i];
		i++;
	}
	var_value[i] = '\0';
	return (var_value);
}

char	*extract_var_name(char *arg)
{
	char	*var_name;
	int		i;

	i = 0;
	while (arg[i] != '=' && arg[i] != '+' && arg[i] != '\0')
		i++;
	var_name = malloc(sizeof(char) * i + 1);
	i = 0;
	while (arg[i] != '=' && arg[i] != '+' && arg[i] != '\0')
	{
		var_name[i] = arg[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}
