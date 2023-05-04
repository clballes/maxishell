/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:09 by clballes          #+#    #+#             */
/*   Updated: 2023/04/28 12:22:13 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	print_list (t_env **list_env)
{
	t_env *temp;

	temp = *list_env;
	while (temp)
	{
		if (temp->print == 0)
			printf("declare -x %s\n",temp->name);
		else
			printf("declare -x %s=\"%s\"\n",temp->name, temp->content);
		temp = temp->next;
	}
}

void	sort_list(t_env **list_env)
{
	int		i;
	t_env	*temp;
	t_env	*temp2;
	t_env	*temp3;
	
	i = 0;
	temp3 = *list_env;
	temp = *list_env;	
	temp2 = temp->next;
	while(temp && temp->next)
	{
		if (ft_strncmp(temp->name, temp2->name, ft_strlen(temp->name)) > 0) //no estan ordenados
		{
			swap(&temp);
			if (temp2->previous == 0)
				*list_env = temp2;
			temp = *list_env;
			temp2 = temp->next;
		}
		else
		{
			temp = temp->next;
			if (temp2)
				temp2 = temp2->next;
		}
	}
}

void	add_new(t_all *all, char *arg)
{
	char	**cont_name;
	
	if (check_equal(all->node) == 0) //si no tenim iguals, ha dapareixer al export no al env
	{
		all->list_env->temporal = lst_new_env(arg, NULL);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		all->list_env->temporal->print = 0;
		sort_list(&all->list_env);
	}
	else //si tenim iguals han dapareixer a les dos
	{
		cont_name = ft_split(arg, '=');
		all->list_env->temporal = lst_new_env(cont_name[0], cont_name[1]);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		all->list_env->temporal->print = 1;
		free(cont_name);
		sort_list(&all->list_env);
	}
}

void	exec_export(t_all *all)
{
	int	i;
	int j;
	t_env	*temp;

	temp = all->list_env;
	i = 0;
	j = 1;
	while(all->node->args[i])
		i++;
	if (i == 1) //si tenim nomes export
	{
		sort_list(&all->list_env);
		print_list(&all->list_env);
	}
	else //si tenim arguments
	{
		check_arg(all->node->args);
		while(all->node->args[j])
		{
			// check_repeat();
			add_new(all, all->node->args[j]);
			j++;
		}
	}
}