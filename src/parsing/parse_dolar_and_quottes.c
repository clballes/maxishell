/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_and_quottes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:59:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/22 17:19:13 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

char *	join_tokens(char **splitted)
{
	int i;
	char *joined;
	i = 1;
	joined = ft_strdup(splitted[0]);
	while(splitted[i])
	{
		
		joined = ft_strjoin(joined," ", 1 , 0);
		joined = ft_strjoin(joined,splitted[i], 1 , 1);
		
		i++;
	}
	free(splitted[0]);
	free(splitted);
	return (joined);
}

void clean_tokens(t_all *all, t_cmd *node)
{
	int i;
	char *result;
	char **splitted;
	i = 0;

	result = NULL;
	while (node->args[i])
	{

		result = expand_dolar(ft_strdup(node->args[i]), all);
		splitted = ft_split_tokens(result, ' ', all);
		free(result);
		result = join_tokens(splitted);
		result = manage_quottes(result);
		free(node->args[i]);
		node->args[i] = result;																
		// printf("NODE_ARGS:%p la i es:%d\n", node->args[i], i);
		i++;
	}
}

int final_tokens_in_nodes(t_all *all)
{
	t_cmd *first_node; // guardamos aqui el primer elemento de la lista
	first_node = all->node;
	while (all->node) // recorremos la lista
	{
		clean_tokens(all, all->node);
		lst_last(&all->node)->cmd = lst_last(&all->node)->args[0];
		all->node = all->node->next;
	}
	all->node = first_node;
	return (0);
}