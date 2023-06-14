/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_and_quottes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:59:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/14 15:58:36 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"
#include "../inc/redirections.h"

int	double_array_len(char **array);

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
	// char	**splitted;
	// char	**new;
	(void)all;
	i = 0;
	result = NULL;
	while (node->args[i])
	{
		result = manage_quottes(ft_strdup(node->args[i]));
		free(node->args[i]);
		node->args[i] = result;
		if(ft_strncmp(node->args[0], "", 2) == 0 || ft_strncmp(node->args[1], "", 2) == 0)
		{
			all->node->empty_string = 1;
		}
		i++;
	}
	

}

int	double_array_len(char **array)
{
	int i;
	
	i = 0;
	while (array[i] != NULL)
	{
		i++;
	}
	return(i);
}

void	clean_file_name(t_all *all, t_redir **redir)
{
	int		i;
	char	*result;

	t_redir	*temp;
	(void)all;
	i = 0;
	result = NULL;
	temp = *redir;
	while (temp)
	{
	
		result = manage_quottes(ft_strdup(temp->file_name));
		free(temp->file_name);
		temp->file_name = result;
		temp = temp->next;
	}
}


int	final_tokens_in_nodes(t_all *all)
{
	t_cmd	*first_node;

	first_node = all->node;
	while (all->node)
	{
		all->node->n_args  = 0;
		clean_tokens(all, all->node);
		clean_file_name(all, &all->node->redir);
		all->node->cmd = all->node->args[0];
		all->node->n_args = double_array_len(all->node->args);
		all->node = all->node->next;
	}
	
	all->node = first_node;
	return (0);
}
