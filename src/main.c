/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/04/27 16:56:59 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int	have_pipes(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

static char	*get_line(void)
{
	char		*line;
	const char	*prompt;

	prompt = "Bienvenid@ a Maxishell: ";
	line = readline(prompt);
	if (!line)
		exit(0); //funcion de error
	return (line);
}

static void	analyze_line(char *all_line, t_all *pipes)
{
	int		res;
	int		i;
	char	**splitted;

	i = 0;
	res = have_pipes(all_line);
	splitted = ft_split(all_line, '|');
	// clean_args(splitted); //doblepuntero
	while (i < (res + 1) && splitted[i])
	{
		pipes->node = lst_new(splitted[i]);
		lst_add_back(&pipes->node, pipes->node);
		pipes->node->args = ft_split(splitted[i], ' ');
		pipes->node->cmd = pipes->node->args[0];
		pipes->node = pipes->node->next;
		i++;
	}
	//free (splitted) while 
	//free (pipes node args) while
}

void	exec_cmd(t_all *all)
{
	if (ft_strncmp(all->node->cmd, "echo", 4) == 0)
		exec_echo(all->node);
	else if (ft_strncmp(all->node->cmd, "cd", 2) == 0)
		printf("he entradoooo CD\n");
	else if (ft_strncmp(all->node->cmd, "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strncmp(all->node->cmd, "export", 6) == 0)
		exec_export(&all->list_env);
	else if (ft_strncmp(all->node->cmd, "unset", 5) == 0)
		printf("he entradoooo UNSET \n");
	else if (ft_strncmp(all->node->cmd, "env", 3) == 0)
		exec_env(&all->list_env);
	else if (ft_strncmp(all->node->cmd, "exit", 4) == 0)
		exec_exit(all->node);
	else
		printf("hemos d eencontar el path de los otros\n");
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_all	*all;

	(void)argc;
	(void)argv;
	line = NULL;
	all = malloc(sizeof(t_all));
	if (!all)
		exit(0);
	all->env = env;
	env_list(all); //malloc lista
	while (1)
	{
		// get_env();
		line = get_line();
		analyze_line(line, all);
		exec_cmd(all);
		free(line); //readline hace malloc
	}
	return (0);
}
