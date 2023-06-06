/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_list_pipes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:01:35 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/06 20:47:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"
#include "../inc/redirections.h"

t_cmd *create_redir_list(t_cmd *node, t_all *all);
char *clean_line_redir(char *line, t_all *all);

// Esta funcion me extrae el comando que separan los pipes dependiendo 
// si es el ultimo o no
char	*save_line_depends_on_position(char *line, int start, int i)
{
	char	*line_to_return;

	if (line[i + 1] == '\0')
		line_to_return = ft_substr(line, start, i + 1 - start);
	else
		line_to_return = ft_substr(line, start, i - start); //TODO cada substring hace MALLOC HAY QUE HACER FREE
	return (line_to_return);
}

//Esta funcion recorre la string si encuentra quotes se activa una 
//variable para que en el caso de que haya un pipe dentro de comillas no nos lo
//coja como un real pipe Si encuentra un pipe real o ya no quedan pipes
//y estamos al final de la linea lo que hace es extraer la linea y guardar las 
//nuevas posiciones de i,count,start para que la proxima vez que al crear
//un nodo se llame a esta función siga por donde se quedo.
//Devuelve esa linea  que en la función de analize line lo introducimos 
//como contenido del nodo.
char	*content_list(char *line, bool init, t_all *all)
{
	static int	i;
	static int	start;
	char		*line_split_by_pipes;

	line_split_by_pipes = NULL;
	if (init)
	{
		i = 0;
		start = 0;
	}
	all->quotes.has_quote = 0;
	while (line[i] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
		if ((line[i] == '|' && !all->quotes.has_quote) || \
			(line[i + 1] == '\0'))
		{	
			line_split_by_pipes = save_line_depends_on_position(line, start, i);
			start = i + 1;
			i++;
			break ;
		}
		i++;
	}
	return (line_split_by_pipes);
}
// Cuenta los pipes reales que hay, si hay pipes entre comillas no lo cuenta.
// Con el numero de pipes sabremos el numero de t_cmd que necesitamos para
// el malloc.
int number_of_pipes(char *line, t_all *all)
{
	int i;
	int count;

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

void create_list_pipes(char *all_line, t_all *all)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	all->n_pipes = number_of_pipes(all_line, all);
	while (i < (all->n_pipes + 1))									//solo tenemos demomento la linea all_line malloc
	{
		if (i == 0)
			temp = lst_new(content_list(all_line, true, all));		//si temp es null entonces liberas todo
		else
			temp = lst_new(content_list(all_line, false, all));
		if (temp == NULL)
			free_lists_and_line(all);
		//printear %p para saber si es el mismo puntero el temp 
		temp->line = ft_strtrim_free_s1(temp->line, " ");
		temp = create_redir_list(temp, all);
		temp->line = clean_line_redir(temp->line, all);//liberar el temp->line dentroo
		//printear %p para saber si es el mismo puntero el temp 
		//tenemos que meter aqui una funcion que nos mire si hay redirecciones y actue en consecuencia
		// si temp->line = echo hola > file1 adios tenemos que conseguir que temp->line sea echo hola adios
		// y guardar el tipo de redireccion y el nombre de archivo
		printf("line_despues de redir clean = %s\n", temp->line);
		lst_add_back(&all->node, temp);
		//printear %p para saber si es el mismo puntero el temp 
		lst_last(&all->node)->args = ft_split_tokens(temp->line, ' ', all);
		i++;
	}
	final_tokens_in_nodes(all);
}

int number_of_redirs(char *line, t_all *all)
{
	int i;
	int n_redir;
	
	i = 0;
	n_redir = 0;
	while(line[i])
	{
		if((line[i] == '>' || line[i] == '<')&& !all->quotes.has_quote)
		{
			n_redir++;
			if((line[i] == '>' || line[i] == '<')&& !all->quotes.has_quote)
				i++;
		}
		i++;
	}	
	return(n_redir);
}

t_cmd *create_redir_list(t_cmd *node, t_all *all)
{
	int i;

	i = 0;
	t_redir *temp;
	node->n_redir = number_of_redirs(node->line, all);
	while(node->n_redir)
	{
		temp = lst_new_redir(file_name(node->line, all), redir_type(node->line, all));
		if (temp == NULL)
			free_lists_and_line(all);
		lst_add_back_redir(&node->redir, temp);
		node->n_redir--;
	}
	return(node);
}


char *clean_line_redir(char *line, t_all *all)
{
	int i;
	char *before;
	char *new_line;
	
	i = 0;
	new_line = NULL;
	while(line[i])
	{
		if((line[i] == '>' || line[i] == '<')&& !all->quotes.has_quote)
		{
			before = ft_substr(line, 0, i);
			i++;
			if (line[i] == '>' || line[i] == '<')
				i++;
			while(ft_is_space(line[i]))
				i++;
			while(!ft_is_space(line[i]) && line[i] != '\0')
				i++;
			// if(line[i])
			new_line = ft_strjoin(before, line + i, 0, 0);
			// else
			// 	new_line = ft_strjoin(before, "", 0, 0);
		}
		i++;
	}
	if(new_line)
		return(new_line);
	return(line);
}
