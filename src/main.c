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
#include <errno.h>

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
int	search_path(t_all *all)
{
	char	*res;
	char	**split_path;
	int		i;
	char	*new_path;

	i = 0;
	res = getenv("PATH");
	split_path = ft_split(res, ':');
	while(split_path[i])
	{
		if (all->node->args[0][0] != '/')
			new_path = ft_strjoin_mini(split_path[i], all->node->args[0]); //join modificat em passo de lineas
		else
			new_path = ft_strjoin(split_path[i], all->node->args[0]); //join modificat em passo de lineas
		if (access(new_path, F_OK | R_OK) == 0)
		{
			printf("we access it\n");
			printf("existeee %s\n",all->node->args[0] );
			execve(new_path, &all->node->args[0], NULL);
			free(new_path); //free del join
			return (0);
		}
		// if (errno == EACCES) {
        //     printf("%s is not readable: permission denied\n", new_path);
        // } else if (errno == ENOENT) {
        //     printf("%s does not exist\n", new_path);
        // } else {
        //     perror("access");
        // }
		i++;
	}
	free_arr(split_path); //free del split
	return (1);
}

void	exec_cmd(t_all *all)
{
	if (ft_strncmp(all->node->cmd, "echo", 5) == 0)
		exec_echo(all->node);
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
		if (search_path(all) == 0)
			all->exit = 0;
		else
		{
			ft_putstrshell_fd("bash: &: command not found", 2, all->node->args, all);
			write(2, "\n", 1);
		}
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
