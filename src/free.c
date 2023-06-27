/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:45:47 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 12:53:42 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void	lstfree_redir(t_redir **lst);

void	lstfree_cmd(t_cmd **lst)
{
	t_cmd	*temp;

	temp = *lst;
	while (temp != NULL)
	{
		if (temp->args != NULL)
			free_arr(temp->args);
		if (temp->line)
			free(temp->line);
		if (temp->redir)
			lstfree_redir(&temp->redir);
		free(temp);
		temp = temp->next;
	}
	*lst = NULL;
}

void	lstfree_redir(t_redir **lst)
{
	t_redir	*temp;

	temp = *lst;
	while (temp)
	{
		free(temp->file_name);
		free (temp);
		temp = temp->next;
	}
	*lst = NULL;
}

void	lstfree_env(t_env **lst)
{
	t_env	*temp;

	while (*lst != NULL)
	{
		temp = *lst;
		while (temp != NULL)
		{
			free(temp->name);
			free(temp->content);
			free (temp);
			temp = temp->next;
		}
		*lst = NULL;
	}
}

void	free_arr(char **array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (array[len])
		len++;
	while (i < len)
	{
		free (array[i]);
		i++;
	}
	free (array);
}

void	free_lists_and_line(t_all *all)
{
	lstfree_cmd(&all->node);
	if (!all->env_i)
		lstfree_env(&all->list_env);
	free(all->all_line);
	free(all);
	exit(all->exit);
}
