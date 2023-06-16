/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:38:25 by clballes          #+#    #+#             */
/*   Updated: 2023/05/12 14:01:28 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	check_n(char *arg)
{
	int	i;

	if (arg[0] == '-' && arg[1] == 'n')
	{
		i = 2;
		while (arg[i] == 'n' && arg[i] != '\0')
			i++;
		if (arg[i] == '\0')
			return (TRUE);
	}
	return (FALSE);
}

void	exec_echo(t_cmd *builtins, t_all *all)
{
	int	i;
	int	printline;

	i = 1;
	printline = TRUE;
	all->exit = 0;
	while (builtins->args[i] && check_n(builtins->args[i]))
	{
		printline = FALSE;
		i++;
	}
	while (builtins->args[i])
	{
		printf("%s", builtins->args[i]);
		if (builtins->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (printline)
		printf("\n");
}