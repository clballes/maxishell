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
		printf("valor en lista:%s\n",temp_a->name);
		temp_a = temp_a->next;
	}
}
void	sort_list(t_env **list_env)
{
	int	i;
	t_env *temp;
	t_env *temp2;
	
	i = 0;
	temp = *list_env;
	temp2 = temp->next;
	printf("el temp ANTES DE ENTRAR EN EL IF %s\n", temp->name);

	while(temp)
	{
		if (ft_strncmp(temp->name, temp2->name, ft_strlen(temp->name)) > 0) //no estan ordenados
		{
			// printf("el temp name %s\n", temp->name);
			// printf("el temp name next %s\n", temp2->name);
			swap(&temp);
			temp = *list_env;
			temp2 = temp->next;
			
			// printf("el temp IGUAL %s\n", temp->next->name);
		}
		if (ft_strncmp(temp->name, temp2->name, ft_strlen(temp->name)) < 0) //si estas ordenado
		{
			// printf("holaaaa\n");
			temp = temp->next;	
			temp2 = temp2->next;
		}
	}
}



void	exec_export(t_env **list_env)
{
	sort_list(list_env);
	print_list(list_env);
}