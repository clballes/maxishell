/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:09 by clballes          #+#    #+#             */
/*   Updated: 2023/05/04 10:18:21 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	print_list(t_env **list_env)
{
	t_env	*temp;

	temp = *list_env;
	while (temp)
	{
		if (temp->print == 0)
			printf("declare -x %s\n", temp->name);
		else
			printf("declare -x %s=\"%s\"\n", temp->name, temp->content);
		temp = temp->next;
	}
}

void	sort_list(t_env **list_env)
{
	int		i;
	t_env	*temp;
	t_env	*temp2;

	i = 0;
	temp = *list_env;
	temp2 = temp->next;
	while (temp && temp->next)
	{
		if (ft_strncmp(temp->name, temp2->name,
				ft_strlen(temp->name)) > 0)
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

int	ft_repeat(t_all *all, char *res, char *arg)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if ((ft_strncmp(temp->name, arg, ft_strlen(temp->name))) == 0)
		{
			change_var_list(res, temp);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	add_new(t_all *all, char *arg)
{
	char	**cont_name;
	char	*res;

	if (all->node->equal == 0)
	{
		if (ft_repeat(all, NULL, arg) == 1)
			return ;
		all->list_env->temporal = lst_new_env(arg, NULL);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		all->list_env->temporal->print = 0;
	}
	else
	{
		if (all->list_env->concatenate == 1)
		{
			res = ft_strchr(arg, '=');
			res++;
			cont_name = ft_split(arg, '+');
		}
		//hola+=o ---- hola=o
		else
		{
			res = ft_strchr(arg, '=');
			printf("le res es %s\n", res);
			res++;
			cont_name = ft_split(arg, '=');
		}
			printf("el cont name es %s\n", cont_name[0]);
		if (ft_repeat(all, res, cont_name[0]) == 1)
			return ;
		all->list_env->temporal = lst_new_env(cont_name[0], res);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		all->list_env->temporal->print = 1;
		// free(cont_name[1]); //nose malloc como limiparlo
		free(cont_name);
	}
	sort_list(&all->list_env);
}

void	exec_export(t_all *all)
{
	int		i;
	int		j;
	t_env	*temp;

	temp = all->list_env;
	all->list_env->concatenate = 0;
	i = 0;
	j = 1;
	while (all->node->args[i])
		i++;
	if (i == 1)
	{
		sort_list(&all->list_env);
		print_list(&all->list_env);
	}
	else
	{
		if (check_equal(all->node, all) != 0)
			check_arg(all);
		while (all->node->args[j])
		{
			add_new(all, all->node->args[j]);
			j++;
		}
	}
}
