/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:22:09 by clballes          #+#    #+#             */
/*   Updated: 2023/05/22 15:49:13 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	ft_repeat(t_all *all, char *res, char *arg)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if ((ft_strncmp(temp->name, arg, ft_strlen(arg) + 1)) == 0) 
		{
			if (all->list_env->concatenate == 1)
				temp->content = ft_strjoin(temp->content, res, 0, 0); //ojo el
			else if ((all->list_env->concatenate == 0) && (res == NULL))
			{
				if (temp->content) //si printejem hola=a i despres, hola, necessito q ess qedi el valor atnerior
					temp->print = 1;		
				else
					temp->print = 0; 
			}
			else if ((all->list_env->concatenate == 0)
				|| (all->node->equal != 0))
			{
				change_var_list(res, temp);
				temp->print = 1;
			}
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

// //Esto abria que revisarlo mejor 
// char *extract_var_value(char *arg)
// {
// 	char *var_value;
// 	int i;

// 	i = 0;
// 	while(*arg != '=' && *arg != '+' && *arg != '\0')
// 		arg++;
// 	if (*arg == '+')
// 		arg++;
// 	if (*arg == '=')
// 		arg++;
// 	if (*arg == '\0')
// 		return NULL;
// 	while(arg[i] != '=' && arg[i] != '+' && arg[i] != '\0')
// 		i++;
	
// 	var_value = malloc(sizeof(char) * i + 1);
// 	i = 0;
// 	while(arg[i] != '\0')
// 	{
// 		var_value[i] = arg[i];
// 		i++;
// 	}
// 	var_value[i] = '\0';
// 	return (var_value);
// }

// char *extract_var_name(char *arg)
// {
// 	char *var_name;
// 	int i;

// 	while(arg[i] != '=' && arg[i] != '+' && arg[i] != '\0')
// 		i++;
// 	var_name = malloc(sizeof(char) * i + 1);
// 	i = 0;
// 	while(arg[i] != '=' && arg[i] != '+' && arg[i] != '\0')
// 	{
// 		var_name[i] = arg[i];
// 		i++;
// 	}
// 	var_name[i] = '\0';
// 	return (var_name);
// }
//en vez de con split hacer una funcion que devuelva el nombre y otra que devuelva solo 
//el contenido 
//NO TENEMOS MALLOC PARA EL RES por eso cada vez se me guarda una cosa 

void	add_equal_arg(t_all *all, char *arg)
{
	char	**cont_name;
	char	*res;

	res = ft_strchr(arg, '=');
	res++;
	if (all->list_env->concatenate == 1)
		cont_name = ft_split(arg, '+');
	else
		cont_name = ft_split(arg, '=');
	if (ft_repeat(all, res, cont_name[0]) == 0)
	{
		all->list_env->temporal = lst_new_env(cont_name[0], res);
		lst_add_back_env(&all->list_env, all->list_env->temporal);
		all->list_env->temporal->print = 1;
	}
	free(cont_name);
}

void	add_new(t_all *all, char *arg)
{
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
		add_equal_arg(all, arg);
	}
	sort_list(&all->list_env);
}

void	exec_export(t_all *all)
{
	int		i;
	int		j;

	all->list_env->concatenate = 0;
	i = 0;
	j = 1;
	while (all->node->args[i]) //esto me lo pasara alba
		i++;
	if (i == 1)
	{
		sort_list(&all->list_env);
		print_list(&all->list_env);
	}
	else
	{
		while (all->node->args[j])
		{
			check_arg(all, all->node->args[j]); //em diu sihi han iguals
			add_new(all, all->node->args[j]);
			all->list_env->concatenate = 0;
			j++;
		}
	}
}
