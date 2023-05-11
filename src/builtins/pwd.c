/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:24 by clballes          #+#    #+#             */
/*   Updated: 2023/04/28 12:22:26 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	exec_pwd(void)
{
	char	pwd[1024];
	char	*res;
	int		i;

	i = 0;
	res = getcwd(pwd, sizeof(pwd));
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		while (res[i])
		{
			write(1, &res[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
	else
	{
		perror("getcwd() error");
		return (1);
	}
	return (0);
}
