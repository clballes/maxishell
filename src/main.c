
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/05/19 11:49:47 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/heredoc.h"
#include "../inc/parsing.h"
#include "../inc/interactive.h"
#include <stdbool.h>
#include <stdlib.h>
// #include <errno.h>

// Lee la linea del promps si algo falla sale y sino la devuelve para
//  empezar a analizarla
char *get_line(void)
{
	char *line;
	const char *prompt;

	prompt = "\x1b[0;35mBienvenid@ a Maxishell\x1b[0m: ";
	line = readline(prompt);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		exit(0);
	}
	// if (!line)
	// 	exit(0); //funcion de error
	return (line);
}


void	other_cmd(t_all *all)
{
	int	i;

	i = -1;
	while (all->node->args[0][i++])
	{
		if (all->node->args[0][i] == '/')
		{
			all->absolute = 1;
			break;
		}
	}
	i = 0;
	if (all->node->args[0][i] == '/' || all->absolute == 1 || all->node->args[0][i] == '.')
	{
		execve_path(all, all->node->args[0]);
		all->absolute = 0;
	}
	else if (search_path(all) == 0)
		all->exit = 0; //comprobar que sea este el num salida
	else
	{
		ft_putstrshell_fd("minishell: &: command not found", 2, all, 0);
		write(2, "\n", 1);
	}
}

void exec_cmd(t_all *all, t_cmd *node)
{
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
		exec_echo(node);
	else if (ft_strncmp(all->node->cmd, "cd", 3) == 0)
		exec_cd(all);
	else if (ft_strncmp(all->node->cmd, "pwd", 4) == 0)
		exec_pwd(all);
	else if (ft_strncmp(all->node->cmd, "export", 7) == 0)
		exec_export(all);
	else if (ft_strncmp(all->node->cmd, "unset", 6) == 0)
		exec_unset(all);
	else if (ft_strncmp(all->node->cmd, "env", 4) == 0)
		exec_env(all);
	else if (ft_strncmp(all->node->cmd, "exit", 5) == 0)
		exec_exit(all);
	else
		other_cmd(all);
}

int main(int argc, char **argv, char **env)
{
	t_all *all;

	(void)argc;
	(void)argv;
	all = ft_calloc(1, sizeof(t_all));
	if (!all)
		exit(0);
	all->env = env;
	init_struct(all);//init podria allocar all y el env  para quitarnos lineas
	while (1)
	{
		all->all_line = get_line();
		if (all->all_line[0] == '\0')
		{
			free(all->all_line);
		// 	system("leaks minishell");
		// 	exit(0);
			continue;
		}
		add_history(all->all_line);
		// heredoc(all);
		if (valid_clean_line(all->all_line, all) == 0)
		{
			create_list_pipes(all->all_line,all);
			minishell_starts(all);
		}
		free(all->all_line);
		lstfree_cmd(&all->node); //free cmd hay q mirar si va aqui
	}
	return (0);
}