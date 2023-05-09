/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/05/08 13:39:11 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/parsing.h"
#include <stdbool.h>

//Lee la linea del promps si algo falla sale y sino la devuelve para 
// empezar a analizarla
static char	*get_line(void)
{
	char		*line;
	// const char	*prompt;

	// prompt = "Bienvenid@ a Maxishell: ";
	// line = readline(prompt);
	line = readline("minishell $");
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		exit (0);
	}
	// if (!line)
	// 	exit(0); //funcion de error
	return (line);
}

// Cuenta los pipes reales que hay, si hay pipes entre comillas no lo cuenta.
// Con el numero de pipes sabremos el numero de t_cmd que necesitamos para 
// el malloc.
int	number_of_pipes(char *line, t_all *all)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	all->quotes.has_quote = 0;
	while (line[i] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
		if (line[i] == '|' && !all->quotes.has_quote)
		{
			count++;
		}
		i++;
	}
	return (count);
}

static int	analyze_line(char *all_line, t_all *all)
{
	int	i;
	t_cmd *temp;
	
	i = 0;
	if (valid_clean_line(all_line, all) != 0)
		return (1);
	all->n_pipes = number_of_pipes(all_line, all);
	while (i < (all->n_pipes + 1))
	{
		if (i == 0)
			temp = lst_new(content_list(all_line, true, all));
		else
			temp = lst_new(content_list(all_line, false, all));
		lst_add_back(&all->node, temp);
		temp->line = ft_strtrim_free_s1(temp->line, " ");
		all->node->args = ft_split_tokens(temp->line, ' ', all);
		all->node->cmd = all->node->args[0];
		i++;
	}
	// final_tokens(all);
	return (0);
	//free (all->node->args) while (array doble puntero)
	//free (all->node) while (lista)
	//free all->node->line
	//free all->node->cmd
}

void	exec_cmd(t_all *all)
{
	if (ft_strncmp(all->node->cmd, "echo", 5) == 0)
	{
		all->exit = exec_echo(all->node, all->exit);
		printf("all exit %d\n", all->exit);
	}
	else if (ft_strncmp(all->node->cmd, "cd", 3) == 0)
		exec_cd(all);
	else if (ft_strncmp(all->node->cmd, "pwd", 4) == 0)
		exec_pwd();
	else if (ft_strncmp(all->node->cmd, "export", 7) == 0)
		exec_export(all);
	else if (ft_strncmp(all->node->cmd, "unset", 6) == 0)
		exec_unset(all);
	else if (ft_strncmp(all->node->cmd, "env", 4) == 0)
		exec_env(&all->list_env);
	else if (ft_strncmp(all->node->cmd, "exit", 5) == 0)
		exec_exit(all);
	else
	{
		DIR *res = opendir("/Users/clballes/miniconda3/bin");
		printf("el rsultado esss %p\n", (void*)res);
		printf("hemos de encontar el path de los otros\n");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;

	(void) argc;
	(void) argv;
	all = ft_calloc(1, sizeof(t_all));
	if (!all)
		exit(0);
	all->env = env;
	init_struct(all);
	while (1)
	{
		
		all->all_line = get_line();
		if (analyze_line(all->all_line, all) == 0)
		{
			exec_cmd(all);
			free(all->all_line); //readline hace malloc
			lstfree(&all->node);
		}
	}
	return (0);
}
