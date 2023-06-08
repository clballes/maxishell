/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:35:30 by clballes          #+#    #+#             */
/*   Updated: 2023/05/09 17:42:04 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	env_list(t_all *all)
{
	t_env	*temp;
	int		shl_level;
	char	**cont_name;
	int		i;

	i = 0;
	all->list_env = NULL;
	shl_level = 1;
	while (all->env[i])
	{
		cont_name = ft_split(all->env[i], '=');
		if (ft_strncmp(cont_name[0], "SHLVL", ft_strlen(cont_name[0])) == 0)
		{
			shl_level = ft_atoi(cont_name[1]);
			shl_level++;
			free(cont_name[1]);
			cont_name[1] = ft_itoa(shl_level);
		}
		temp = lst_new_env(cont_name[0], cont_name[1]);
		lst_add_back_env(&all->list_env, temp);
		free(cont_name);
		temp->print = 1;
		all->list_env->temporal = temp;
		temp = temp->next;
		i++;
	}
}

void	exec_env(t_all *all)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if (temp->print == 1)
		{
			if (ft_strncmp("OLDPWD",
					temp->name, ft_strlen(temp->name)) == 0 && (all->cd == 0))
			{
				if (temp->next == NULL)
					break ;
				temp = temp->next;
			}
			printf("%s=%s\n", temp->name, temp->content);
		}
		temp = temp->next;
	}
}
