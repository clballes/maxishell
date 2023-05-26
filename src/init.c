/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:28:57 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/26 11:01:19 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_env_i(t_all *all)
{
	char	pwd[1024];

 	all->minishell = all->minishell - 1;
	all->env = ft_calloc(4 + 1, sizeof(char *));
	all->env[0] = getcwd(pwd, sizeof(pwd));
	all->env[3] = ft_strjoin("OLDPWD=", all->env[0], 0, 0);
	all->env[0] = ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd)), 0, 0);
	all->env[1] = ft_strjoin("SHLVL=", &all->minishell, 0, 0);
	all->env[2] = ft_strjoin("_=", "/usr/bin/env", 0, 0);
	all->env[4] = NULL;
	env_list(all);
	free_arr(all->env);
}

void	init_struct(t_all *all)
{
	all->quotes.has_quote = 0;
	all->quotes.found = '\0';
	all->exit = 0;
	all->bar = 0;
	all->cd = 0;
	all->absolute = 0;
	all->minishell = 50;
	if (all->env[0] != NULL)
		env_list(all);
	else
		init_env_i(all);
}