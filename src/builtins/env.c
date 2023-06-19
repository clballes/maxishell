/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:35:30 by clballes          #+#    #+#             */
/*   Updated: 2023/06/13 16:21:45 by albagarc         ###   ########.fr       */
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
		if (ft_strncmp(cont_name[0], "SHLVL", ft_strlen(cont_name[0])) == 0 && all->env_i == 0)
		{
			int new_shlvl = ft_atoi(cont_name[1]);
			if (new_shlvl < 0)
				shl_level = -1;
			else if (new_shlvl > 999)
			{
				new_shlvl++;
				char *var = ft_itoa(new_shlvl);
				write_dyn_err("bash: warning: shell level (&) too high, resetting to 1", var);
				shl_level = 0;
			}
			else
				shl_level = ft_atoi(cont_name[1]);
			shl_level++;
			free(cont_name[1]);
			cont_name[1] = ft_itoa(shl_level); //poosible leak pero no no da leak
		}
		temp = lst_new_env(cont_name[0], cont_name[1]);
		lst_add_back_env(&all->list_env, temp);
		free(cont_name);
		temp->print = 1;
		all->list_env->temporal = temp;
		temp = temp->next;
		i++;
	}
	
	all->env_array = list_to_double_pointer(&all->list_env);
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


char	**list_to_double_pointer(t_env **list)
{
	t_env *temp;
	char **env_array;
	char *aux;
	char *result;
	int i;

	i = lst_size_env(list);
	env_array = ft_calloc(i + 1 ,sizeof(char *));
	i = 0;
	temp = *list;
	while(temp)
	{
		aux = ft_strjoin(temp->name, "=", 0, 0);
		result = ft_strjoin(aux, temp->content, 1, 0);
		env_array[i] = result;
		i++;
		temp = temp->next;
	}
	env_array[i] = NULL;
	return(env_array);
}