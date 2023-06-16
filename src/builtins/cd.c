/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:49:53 by clballes          #+#    #+#             */
/*   Updated: 2023/06/13 16:21:31 by albagarc         ###   ########.fr       */
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
		if (ft_strncmp(temp->name, "PWD", ft_strlen(temp->name)) == 0)
			temp->content = all->list_env->new_cd;
		if (ft_strncmp(temp->name, "OLDPWD", ft_strlen(temp->name)) == 0)
			temp->content = all->list_env->current_cd;
		temp = temp->next;
	}
}

void	write_error_cd(t_all *all, char *new_cd, int i)
{
	if (i == 0)
		write_dyn_err("bash: cd: &: Permission denied", all->node->args[1]);		
    if (i == 1)
		write_dyn_err("bash: cd: &: Not a directory", all->node->args[1]);
    if (i == 2)
	{
		if ((ft_strlen(all->node->args[1])) > 255)
			write_dyn_err("bash: cd: &: File name too long", all->node->args[1]);
		else
			write_dyn_err("bash: cd: &: No such file or directory", all->node->args[1]);
	}
    free(new_cd);
    all->exit = 1;
}

int    error_msg(t_all *all, char *new_cd)
{
    struct stat path_stat;

    if (stat(new_cd, &path_stat) == 0)
    {
        if (S_ISDIR(path_stat.st_mode) && (access(new_cd, F_OK | R_OK | W_OK) != 0))
		{
			write_error_cd(all, new_cd, 0);
			return (1);
		}
		else if (!S_ISDIR(path_stat.st_mode))
		{
			write_error_cd(all, new_cd, 1);
			return (1);
		}
    }
    else
	{
		write_error_cd(all, new_cd, 2);
		return (1);	
	}
	return (0);
}

void	create_path(t_all *all)
{
    char	**split_dir;
	char	*new_cd;
	int		i;

	i = 0;
	split_dir = NULL;
	if (all->node->args[1][0] != '/')
    {
        if (ft_strrchr(all->node->args[1], '/') != 0)
		{
			// new_cd = ft_strjoin(all->list_env->current_cd, "/", 0, 0);
			// new_cd = ft_strjoin(ft_strdup(new_cd), split_dir[i], 1, 0);
            split_dir = ft_split(all->node->args[1], '/');
			new_cd = ft_strjoin_path(all->list_env->current_cd, \
				split_dir[i]);
			while (split_dir[i])
			{
				if (error_msg(all, new_cd) == 0)
				{
					free(split_dir[i]);
					i++;
					new_cd = ft_strjoin_path(new_cd, split_dir[i]);
					// new_cd = ft_strjoin(ft_strdup(new_cd), "/", 1, 0);
					// new_cd = ft_strjoin(ft_strdup(new_cd), split_dir[i], 1, 1);
				}
				else
					return ;
			}
		}
		else
			new_cd = ft_strjoin_path(all->list_env->current_cd, \
				all->node->args[1]);
	}
    else
        new_cd = ft_strjoin(all->list_env->current_cd, all->node->args[1], 0, 0);
	error_msg(all, new_cd);
}

int	exec_cd(t_all *all)
{
	if (all->node->args[1] && all->node->args[1][0] == 47
			&& all->node->args[1][1] == 47
			&& (ft_strlen(all->node->args[1]) == 2))
		{
			all->bar = 1;
		}
	all->list_env->current_cd = getcwd(NULL, 0);
	if (all->node->args[1])
	{
		if (chdir(all->node->args[1]) == -1)
		{
			create_path(all);
		}
		else
			all->cd = 1;
	}
	else
	{
		if (chdir(path_direction(all, "HOME")) == -1)
		{
			all->exit = 1;
			write_dyn_err("bash: cd: HOME not set", NULL);
		}
		else
			all->cd = 1;
	}
	all->list_env->new_cd = getcwd(NULL, 0);
	change_env(all);
	return (0);
}