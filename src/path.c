/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:47:16 by clballes          #+#    #+#             */
/*   Updated: 2023/05/30 11:01:58 by albagarc         ###   ########.fr       */
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

void	fork_function(t_all *all, char *new_path)
{
	// pid_t	pid;

	// pid = fork();
	// if (pid == -1)
	// {
	// 	// all->exit = 1
	// 	printf("error en el fork\n");
	// }
	// else if (pid == 0)
	// {

		// fprintf(stderr,"new path:%s all->node->args[0]:%s\n", new_path, all->node->args[0]);
		if (execve(new_path, &all->node->args[0], all->env) != 0)
		{
			ft_putstrshell_fd("bash: &: No such file or directory", 2, all, 0);
			write(2, "\n", 1);
			// all->exit = 1
			exit(all->exit);
		}
	// }
	// else
	// 	waitpid(pid, &all->exit, 0);
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
	return (NULL); //exit que ha fallat
}

int	search_path(t_all *all)
{
	char	*res;
	char	**split_path;
	int		i;
	char	*new_path;

	i = 0;
	res = path_direction(all, "PATH");
	if (res == NULL)
		return (1);
	split_path = ft_split(res, ':'); //mallocs
	while (split_path[i])
	{
		new_path = ft_strjoin_path(split_path[i], all->node->args[0]); //join modificat em passo de lineas
		if (access(new_path, F_OK | R_OK) == 0)
		{
			fork_function(all, new_path);
			free(new_path); //free del join
			free_arr(split_path); //free del split
			return (0);
		}
		i++;
	}
	free(new_path);
	free_arr(split_path); //free del split
	return (1);
}
