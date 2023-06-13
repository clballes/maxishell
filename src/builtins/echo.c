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

void	exec_echo(t_cmd *builtins)
{
	int	i;
	int	printline;

	i = 1;
	printline = TRUE;
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
// int	check_n(char *args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if (ft_strncmp(args, "-n", 2) == 0)
// 		{
// 			i = 2;
// 			while(args[i] == 'n' && args[i])
// 				i++;
// 			if (args[i] == '\0')
// 				return (0); //no hem de fer el satl
// 			else
// 				return (1); //vol dir q si q em de fer el salt -n si
// 		}
// 		i++;
// 	}
// 	return (0); //no hem de fer el salt
// }

// void	exec_echo(t_cmd *builtins)
// {
// 	int	i;
// 	int	res;
// 	int cont;
// 	cont = 0;
// 	i = 0;
// 	res = 0;
// 	int res2 = 1;
// 	if (builtins->args[1])
// 	{
// 		while (builtins->args[++i] && ft_strncmp(builtins->args[i], "-n", 2) == 0)
// 		{
// 			res2 = check_n(builtins->args[i]);
// 			if (res2 == 1)
// 				cont++;
// 		}
// 		if(res2 == 1)
// 			res = 1;
// 		if (cont)
// 		{
// 			i = cont;
// 			res = 1;
// 		}
// 		while (builtins->args[i])
// 		{
// 			printf("%s", builtins->args[i]);
// 			if (builtins->args[i + 1] != NULL)
// 				printf(" ");
// 			i++;
// 		}
// 		if (res == 1)
// 			printf("\n");
// 	}
// 	else
// 		printf("\n");
// }



