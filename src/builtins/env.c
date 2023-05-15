/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:35:30 by clballes          #+#    #+#             */
/*   Updated: 2023/04/27 16:49:08 by clballes         ###   ########.fr       */
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
		temp = lst_new_env(cont_name[0], cont_name[1]);
		lst_add_back_env(&all->list_env, temp);
		free(cont_name);
		temp->print = 1;
		all->list_env->temporal = temp;
		temp = temp->next;
		i++;
	}
}

void	exec_env(t_env **list_env)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = *list_env;
	while (temp)
	{
		if (temp->print == 1)
		{
			if (temp->name == NULL) // con el env -i accede mas alla de valores incluso cuando esnull por eso eta condicion
				break;
			printf("%s=%s\n", temp->name, temp->content);
		}
		temp = temp->next;
	}
}
