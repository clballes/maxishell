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

void	set_index(t_env **list_env)
{
	t_env	*temp;
	char	*alphabet;
	int		j;

	j = 0;
	temp = *list_env;
	alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	temp->index = 0;
	while (temp)
	{
		if (temp->name[0] == alphabet[j])
		{
			temp->index = j;
			printf("el indice es %d\n", temp->index);
			temp = temp->next;
			j = 0;
		}
		else
			j++;
	}
	//el total de nodos es 42 para hacer el solve con el push swap
}

// int	*sort_int_tab(int *tab, unsigned int size)
// {
// 	unsigned int i;
// 	int swap;
	
// 	swap = 0;
// 	while (sort_tab(tab, size))
// 	{
// 		i = 0;
// 		while (i < size - 1)
// 		{
// 			if (tab[i] > tab[i + 1])
// 			{
// 				swap = tab[i];
// 				tab[i] = tab[i + 1];
// 				tab[i + 1] = swap;
// 			}
// 			i++;
// 		}
// 	}
// 	return (tab);
// }

void	order_num(t_env **list_env)
{
	t_env	*temp;
	t_env	*temp2;
	int		j;

	j = 0;
	temp = *list_env;
	temp2 = *list_env;
	while (temp)
	{
		if (temp2->index > temp->next->index)
		{
			swap(list_env);
			temp2 = temp2->next;
		}
		// order_same_num();
		temp = temp->next;
	}
}

void	exec_export(t_env **list_env)
{
	set_index(list_env);
	order_num(list_env);
    // num_compare(list_env);
}