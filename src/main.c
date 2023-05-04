/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:03:36 by clballes          #+#    #+#             */
/*   Updated: 2023/05/04 11:52:30 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"
#include "../inc/parsing.h"
#include <stdbool.h>

//Lee la linea del promps si algo falla sale y sino la devuelve para empezar a analizarla
static char    *get_line()
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
int   number_of_pipes(char *line, t_all *all)
{   
    int i;
    int count;

    i = 0;
    count = 0;
    all->quotes.has_quote = 0;
    while (line[i] != '\0')
    {
		all->quotes.has_quote = is_inside_quotting(line, all, i);
        if (line[i] == '|' && !all->quotes.has_quote)
        {
            count++;
        }
        i++;
    }
    printf("numpipes is:%d\n ", count);
    return(count);
}

static int analyze_line(char *all_line, t_all *all)
{
    
    int i;
    // char **splitted;

    i = 0;
    
    if(clean_all_line(all_line, all) != 0)
        return(1);
    all->n_pipes = number_of_pipes(all_line, all);
    // splitted = ft_split(all_line, '|');//va a desaparecer
    // clean_args(splitted); //doblepuntero
    while (i < (all->n_pipes + 1) /*&& splitted[i]*/)
    {
        if (i == 0)
            all->node = lst_new(content_list(all_line, true, all));
        else
            all->node = lst_new(content_list(all_line, false, all));
        lst_add_back(&all->node, all->node);
        printf("el contenido del nodo es:%s\n", all->node->line);
		all->node->args = ft_split_tokens(all->node->line, ' ', all);
	// TODO HAY QUE TENER EN CUENTA TABULACIONES ESPACIOS ETC IS_SPACE
        printf("arg[0]:%s\n", all->node->args[0]);
        printf("arg[1]:%s\n", all->node->args[1]);
        // printf("arg[1]:%s\n", all->node->args[2]);
        // all->node->args = ft_split(splitted[i], ' ');//aquí va la función que me va a separar los argumentos 
        all->node->cmd = all->node->args[0];
        all->node = all->node->next;
        i++;
    }

    return(0);
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
		exec_exit(all);
	else
		printf("hemos d eencontar el path de los otros\n");
}

int	main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
 
    t_all *all;
    
    // line = NULL;
    all = ft_calloc(1, sizeof(t_all));
    if(!all)
        exit(0);
    all->env = env;
	init_struct(all);
    while (1)
    {
        // get_env();
        all->all_line = get_line();
        if(analyze_line(all->all_line, all) == 0)
        {
            exec_cmd(all);
            free(all->all_line); //readline hace malloc
        }
    }
    return (0);
}
