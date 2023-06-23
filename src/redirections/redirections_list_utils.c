/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:37:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/21 15:22:04 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redir	*lst_new_redir(char *file_name, int redir)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (0);
	new->file_name = file_name;
	new->type = redir;
	new->next = NULL;
	return (new);
}

t_redir	*lst_last_redir(t_redir **lst)
{
	t_redir	*temp;

	temp = *lst;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
	}
	return (temp);
}

void	lst_add_back_redir(t_redir **first, t_redir *new_el)
{
	t_redir	*temp;

	if (*first == NULL)
		*first = new_el;
	else
	{
		temp = lst_last_redir(first);
		temp->next = new_el;
	}
}

int	lst_size_redir(t_redir **lst)
{
	int		i;
	t_redir	*temp;

	i = 0;
	temp = *lst;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
