/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:35:30 by clballes          #+#    #+#             */
/*   Updated: 2023/06/22 16:32:02 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	env_list(t_all *all)
{
	t_env	*temp;
	char	**cont_name;
	int		i;

	i = 0;
	all->list_env = NULL;
	while (all->env[i])
	{
		cont_name = ft_split(all->env[i], '=');
		if (ft_strncmp(cont_name[0], "SHLVL",
				ft_strlen(cont_name[0])) == 0 && all->env_i == 0)
			change_shlvl(all, cont_name[1]);
		temp = lst_new_env(cont_name[0], cont_name[1]);
		lst_add_back_env(&all->list_env, temp);
		free(cont_name);
		temp->print = 1;
		temp = temp->next;
		i++;
	}
	if (!all->exist && all->env_i == 0)
		add_shlvl(temp, all);
	list_to_double_pointer(&all->list_env, all);
}

void	exec_env(t_all *all, t_env **list_env)
{
	t_env	*temp;

	temp = *list_env;
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

void	change_env(t_all *all)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if (ft_strncmp(temp->name, "PWD", ft_strlen(temp->name)) == 0)
		{
			free(temp->content);
			temp->content = all->list_env->new_cd;
		}
		if (ft_strncmp(temp->name, "OLDPWD", ft_strlen(temp->name)) == 0)
		{
			free(temp->content);
			temp->content = all->list_env->current_cd;
		}
		temp = temp->next;
	}
}

char	**list_to_double_pointer(t_env **list, t_all *all)
{
	t_env	*temp;
	char	*aux;
	char	*result;
	int		i;

	i = lst_size_env(list);
	all->env_array = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	temp = *list;
	while (temp)
	{
		aux = ft_strjoin(temp->name, "=", 0, 0);
		result = ft_strjoin(aux, temp->content, 1, 0);
		all->env_array[i] = result;
		i++;
		temp = temp->next;
	}
	all->env_array[i] = NULL;
	return (all->env_array);
}
