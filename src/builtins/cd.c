/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:49:53 by clballes          #+#    #+#             */
/*   Updated: 2023/05/19 11:01:55 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	change_env(t_all *all)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if (all->minishell > 48)
		{
			if (ft_strncmp(temp->name, "SHLVL", ft_strlen(temp->name)) == 0)
			{
				temp->content = &all->minishell;
				break;
			}
		}
		else
		{
			if (ft_strncmp(temp->name, "PWD", ft_strlen(temp->name)) == 0)
				temp->content = all->list_env->new_cd;
			if (ft_strncmp(temp->name, "OLDPWD", ft_strlen(temp->name)) == 0)
				temp->content = all->list_env->current_cd;
		}
		temp = temp->next;
	}
}

void	error_msg(t_all *all) //free malloc perq faig un join
{
	struct stat	path_stat;
	char		*new_cd;

	if (all->node->args[1][0] != '/')
		new_cd = ft_strjoin_path(all->list_env->current_cd, \
				all->node->args[1]);
	else
		new_cd = ft_strjoin(all->list_env->current_cd, all->node->args[1], 0, 0);
	if (stat(new_cd, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode))
		{
			ft_putstrshell_fd("bash: cd: &: Not a directory", 2, all, 1); //aqui passa algo
			write(2, "\n", 1);
			free(new_cd);
			all->exit = 1;
		}
	}
	else
	{
		ft_putstrshell_fd("bash: cd: &: No such file or directory", 2, all, 1);
		write(2, "\n", 1);
		free(new_cd);
		all->exit = 1;
	}
}

int	exec_cd(t_all *all)
{
	if (all->node->args[1] && all->node->args[1][0] == 47
			&& all->node->args[1][1] == 47
			&& (ft_strlen(all->node->args[1]) == 2))
		all->bar = 1;
	all->list_env->current_cd = getcwd(NULL, 0);
	if (all->node->args[1])
	{
		if (chdir(all->node->args[1]) == -1)
			error_msg(all);
		else
			all->cd = 1;
	}
	else
	{
		if (chdir(path_direction(all, "HOME")) == -1)
		{
			all->exit = 1;
			ft_putstrshell_fd("bash: cd: HOME not set", 2, all, 1);
			write(2, "\n", 1);
		}
		else
			all->cd = 1;
	}
	all->list_env->new_cd = getcwd(NULL, 0);
	change_env(all);
	return (0);
}
