/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_and_quottes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:59:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/26 11:04:19 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

char	*join_tokens(char **splitted)
{
	int		i;
	char	*joined;

	i = 1;
	if (splitted[0] != NULL)
		joined = ft_strdup(splitted[0]);
	else
		return (ft_strdup(""));
	while (splitted[i])
	{
		joined = ft_strjoin(joined, " ", 1, 0);
		joined = ft_strjoin(joined, splitted[i], 1, 1);
		i++;
	}
	return (joined);
}

void	clean_tokens(t_all *all, t_cmd *node)
{
	int		i;
	char	*result;
	char	**splitted;

	i = 0;
	result = NULL;
	while (node->args[i])
	{
		result = expand_dolar(ft_strdup(node->args[i]), all);
		splitted = ft_split_tokens(result, ' ', all);
		free(result);
		result = join_tokens(splitted);
		free_arr(splitted);
		result = manage_quottes(result);
		free(node->args[i]);
		node->args[i] = result;
		i++;
	}
}

int	double_array_len(char **array)
{
	int i;
	
	i = 0;
	while (array[i]!= NULL)
	{

		i++;
	}
	return(i);
}

int	final_tokens_in_nodes(t_all *all)
{
	t_cmd	*first_node;

	first_node = all->node;
	while (all->node)
	{
		all->node->n_args  = 0;
		clean_tokens(all, all->node);
		all->node->cmd = all->node->args[0];
		all->node->n_args = double_array_len(all->node->args);
		printf("cmd:%s\n",all->node->cmd);
		all->node = all->node->next;
	}
	all->node = first_node;
	return (0);
}
