/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:47:16 by clballes          #+#    #+#             */
/*   Updated: 2023/06/21 18:18:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	count;

	count = -1;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	new = malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return (0);
	while (s1[++count] != '\0')
		new[count] = s1[count];
	count = -1;
	while (s2[++count] != '\0')
	{
		if (count == 0)
		{
			new[count + i] = '/';
			i++;
		}
		new[count + i] = s2[count];
	}
	new[count + i] = '\0';
	return (new);
}

void	execve_path(t_all *all, char *new_path)
{
	if (execve(new_path, &all->node->args[0], all->env_array) != 0)
	{
		if (new_path[0] == '/')
			all->exit = 127;
		write_dyn_err("bash: &: No such file or directory", all->node->args[0]);
		exit(all->exit);
	}
}

char	*path_direction(t_all *all, char *direction)
{
	t_env	*temp;

	temp = all->list_env;
	while (temp)
	{
		if (ft_strncmp(direction, temp->name, ft_strlen(temp->name)) == 0)
			return (temp->content);
		temp = temp->next;
	}
	return (NULL);
}

void	free_path(char *new_path, char **split_path)
{
	free(new_path);
	free_arr(split_path);
}

int	search_path(t_all *all, t_cmd *node)
{
	char	*res;
	char	**split_path;
	int		i;
	char	*new_path;

	if (node->empty_string)
		return (1);
	i = 0;
	res = path_direction(all, "PATH");
	if (res == NULL)
		return (1);
	split_path = ft_split(res, ':');
	while (split_path[i])
	{
		new_path = ft_strjoin_path(split_path[i], all->node->args[0]);
		if (access(new_path, F_OK | R_OK) == 0)
		{
			execve_path(all, new_path);
			free_path(new_path, split_path);
			return (0);
		}
		i++;
	}
	free_path(new_path, split_path);
	return (1);
}
