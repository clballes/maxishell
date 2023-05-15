/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:28:57 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/03 13:36:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_env_i(t_all *all)
{
	int		i;
	char	pwd[1024];
	char	level_sh;

	i = 0;
	level_sh = 48; //el numeor 1 tenir en compte quan creem un minishell dintre dun minishel
	all->env[0] = getcwd(pwd, sizeof(pwd));
	all->env[3] = ft_strjoin("OLDPWD=", all->env[0]);
	all->env[0] = ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd)));
	all->env[1] = ft_strjoin("SHLVL=", &level_sh);
	all->env[2] = ft_strjoin("_=", "/usr/bin/env"); //mallocsss hevy
	env_list(all);
}

void	init_struct(t_all *all)
{
	all->quotes.has_quote = 0;
	all->exit = 0;
	all->bar = 0;
	all->absolute = 0;
	if (all->env[0] != NULL)
		env_list(all);
	else
		init_env_i(all);		
}