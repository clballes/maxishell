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

void	print_list (t_env **list_a)
{
	t_env *temp_a;

	temp_a = *list_a;
	while (temp_a)
	{
		printf("declare -x %s=\"%s\"\n",temp_a->name, temp_a->content);
		temp_a = temp_a->next;
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

void	exec_export(t_env **list_env)
{
	// print_list(list_env);
	sort_list(list_env);
	print_list(list_env);
}