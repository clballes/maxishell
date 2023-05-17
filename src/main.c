/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/05/17 13:17:31 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/parsing.h"
#include "../inc/interactive.h"
#include <stdbool.h>
// #include <errno.h>

//Lee la linea del promps si algo falla sale y sino la devuelve para 
// empezar a analizarla
char	*get_line(void)
{
	char		*line;
	const char	*prompt;

	prompt = "\x1b[0;35mBienvenid@ a Maxishell\x1b[0m: ";
	line = readline(prompt);
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
		temp->line = ft_strtrim_free_s1(temp->line, " ");
		lst_add_back(&all->node, temp);
		lst_last(&all->node)->args = ft_split_tokens(temp->line, ' ', all);
		lst_last(&all->node)->double_quote = false;
		lst_last(&all->node)->single_quote = false;
		
		// printf("numero de args = %d\n", all->node->n_args);
		i++;
	}
	final_tokens_in_nodes(all);	
		
	return (0);
	//free (all->node->args) while (array doble puntero)
	//free (all->node) while (lista)
	//free all->node->line
	//free all->node->cmd
}

void	exec_cmd(t_all *all)
{
	int i;
	i = -1;
	if (ft_strncmp(all->node->cmd, "echo", 5) == 0)
		exec_echo(all->node);
	else if (ft_strncmp(all->node->cmd, "cd", 3) == 0)
		exec_cd(all);
	else if (ft_strncmp(all->node->cmd, "pwd", 4) == 0)
		exec_pwd(all);
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
		while (all->node->args[0][i++])
		{
			if (all->node->args[0][i] == '/')
			{
				all->absolute = 1;
				break;
			}
		}
		i = 0;
		if (all->node->args[0][i] == '/' || all->absolute == 1)
		{
			fork_function(all, all->node->args[0]);
			all->absolute = 0;
		}
		else if (search_path(all) == 0)
			all->exit = 0; //comprobar que sea este el num salida
		else
		{
			ft_putstrshell_fd("bash: &: command not found", 2, all, 0);
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
		add_history(all->all_line);
		if (analyze_line(all->all_line, all) == 0)
		{
			exec_cmd(all);
			free(all->all_line); //readline hace malloc // addhistory hace free probar si tenemos que hacer nosotras free;
			lstfree(&all->node);
		}
		else
		{
			free(all->all_line); 
			lstfree(&all->node);
		}
	}
	return (0);
}
