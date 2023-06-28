/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 12:58:27 by albagarc         ###   ########.fr       */
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
void	free_cmd_line(t_all *all)
{
	free(all->all_line);
	lstfree_cmd(&all->node);
}

char	*get_line(t_all *all)
{
	char		*line;
	const char	*prompt;

	prompt = "\x1b[0;35mBienvenid@ a Maxishell\x1b[0m: ";
	line = readline(prompt);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 5);
		exit(all->exit);
	}
	return (line);
}

void	other_cmd(t_all *all, t_cmd *node)
{
	int	i;

	i = -1;
	while (all->node->args[0][i++])
	{
		if (all->node->args[0][i] == '/')
		{
			all->absolute = 1;
			break ;
		}
	}
	i = 0;
	if (all->node->args[0][i] == '/' || all->absolute == 1 || \
	all->node->args[0][i] == '.')
	{
		execve_path(all, all->node->args[0]);
		all->absolute = 0;
	}
	else if (search_path(all, node) == 0)
		all->exit = 0;
	else
	{
		all->exit = 127;
		write_dyn_err("minishell: &: command not found", all->node->args[0]);
	}
}

void	exec_cmd(t_all *all, t_cmd *node)
{
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
		exec_echo(node, all);
	else if (ft_strncmp(all->node->cmd, "cd", 3) == 0)
		exec_cd(all);
	else if (ft_strncmp(all->node->cmd, "pwd", 4) == 0)
		exec_pwd(all);
	else if (ft_strncmp(all->node->cmd, "export", 7) == 0)
		exec_export(all);
	else if (ft_strncmp(all->node->cmd, "unset", 6) == 0)
		exec_unset(all);
	else if (ft_strncmp(all->node->cmd, "env", 4) == 0)
		exec_env(all, &all->list_env);
	else if (ft_strncmp(all->node->cmd, "exit", 5) == 0)
		exec_exit(all, node);
	else
		other_cmd(all, node);
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;

	(void)argc;
	(void)argv;
	all = NULL;
	all = init_struct(all, env);
	while (1)
	{
		g_glbl.g_ctrlc = 0;
		init_signal(3, all);
		set_term();
		all->all_line = get_line(all);
		if (all->all_line[0] == '\0')
			continue ;
		add_history(all->all_line);
		if (valid_clean_line(all->all_line, all) == 0)
		{
			create_list_pipes(all->all_line, all);
			minishell_starts(all);
		}
		free_cmd_line(all);
		init_signal(1, all);
	}
	free_lists_and_line(all);
	return (0);
}
