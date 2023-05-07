/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/05/02 09:40:36 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/parsing.h"
#include <stdbool.h>

//Lee la linea del promps si algo falla sale y sino la devuelve para empezar a analizarla
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

// Cuenta los pipes reales que hay, si hay pipes entre comillas no lo cuenta.
// Con el numero de pipes sabremos el numero de t_cmd que necesitamos para el malloc.
int   number_of_pipes(char *line)
{   
    int i;
    int count;
    bool active_quotes;

    i = 0;
    count = 0;
    active_quotes = false;
    while (line[i] != '\0')
    {
        if (line[i] == '\"' || line[i] == '\'')
        {
            if (!active_quotes)
                active_quotes = true;
            else if (active_quotes)
                active_quotes = false;
        }
        if (line[i] == '|' && !active_quotes)
        {
            count++;
        }
        i++;
    }
    // printf("numpipes is:%d\n ", count);
    return(count);
}

static int	analyze_line(char *all_line, t_all *all)
{
	int i;
	char **splitted;

	i = 0;
	all->n_pipes = number_of_pipes(all_line);
	// printf("all_line %s\n", all_line);
	if (clean_all_line(all_line, &all->quotes) != 0)
		return(1);
	splitted = ft_split(all_line, '|');
	// clean_args(splitted); //doblepuntero
	while (i < (all->n_pipes + 1) && splitted[i])
	{
		if (i == 0)
			all->node = lst_new(content_list(all_line, true, all));
		else
			all->node = lst_new(content_list(all_line, false, all));
		lst_add_back(&all->node, all->node);
		// printf("el contenido del nodo es:%s\n", all->node->line);
		all->node->args = ft_split(splitted[i], ' ');//aquí va la función que me va a separar los argumentos 
		all->node->cmd = all->node->args[0];
		all->node = all->node->next;
		i++;
	}
	return (0);
	//free (splitted) while 
	//free (pipes node args) while
}

void	exec_cmd(t_all *all)
{
	if (ft_strncmp(all->node->cmd, "echo", 4) == 0)
		exec_echo(all->node);
	else if (ft_strncmp(all->node->cmd, "cd", 2) == 0)
		exec_cd(all);
	else if (ft_strncmp(all->node->cmd, "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strncmp(all->node->cmd, "export", 6) == 0)
		exec_export(all);
	else if (ft_strncmp(all->node->cmd, "unset", 5) == 0)
		exec_unset(all);
	else if (ft_strncmp(all->node->cmd, "env", 3) == 0)
		exec_env(&all->list_env);
	else if (ft_strncmp(all->node->cmd, "exit", 4) == 0)
		exec_exit(all);
	else
		printf("hemos de encontar el path de los otros\n");
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;

	(void)argc;
	(void)argv;
	// line = NULL;
	all = malloc(sizeof(t_all));
	if (!all)
		exit(0);
	all->env = env;
	env_list(all);
	while (1)
	{
		all->all_line = get_line();
		if (analyze_line(all->all_line, all) == 0)
		{
			// qui hay malloc no resuelto da ROOT LEAK que arrastramos
			exec_cmd(all);
			free(all->all_line); //readline hace malloc
		}
	}
	return (0);
}
