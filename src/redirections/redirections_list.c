/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:05 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/07 13:35:40 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/redirections.h"
#include "../inc/parsing.h"

char	*clean_line_redir(char *line, t_all *all);

static int	identify_redir(char a, char b)
{
	int	redir;

	if (a == '>')
	{
		if (a == b)
			redir = OUTPUT_APPEND;
		else
			redir = OUTPUT_TRUNCATED;
	}
	if (a == '<')
	{
		if (a == b)
			redir = HEREDOC;
		else
			redir = INPUT;
	}
	return (redir);
}

static int	redir_type(char *line, t_all *all)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	all->quotes.has_quote = 0;
	while (line[i] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
		if ((line[i] == '>' || line[i] == '<') && !all->quotes.has_quote)
		{
			redir = identify_redir(line[i], line[i + 1]);
			break ;
		}
		i++;
	}
	return (redir);
}

static char	*file_name(char *line, t_all *all)
{
	int		i;
	int		start;
	char	*file_name;

	i = 0;
	all->quotes.has_quote = 0;
	while (line[i] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
		if ((line[i] == '>' || line[i] == '<') && !all->quotes.has_quote)
		{	
			i++;
			if ((line[i] == '>' || line[i] == '<') && line[i] != '\0')
				i++;
			while (ft_is_space(line[i]) && line[i] != '\0')
				i++;
			start = i;
			while (!ft_is_space(line[i]) && line[i] != '\0' && line[i] != '<' && line[i] != '>')
				i++;
			file_name = ft_substr(line, start, i - start);
			return (file_name);//FREEEEEEE
		}
		i++;
	}
	return (NULL);
}

static int	number_of_redirs(char *line, t_all *all)
{
	int	i;
	int	n_redir;

	i = 0;
	n_redir = 0;
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') && !all->quotes.has_quote)
		{
			n_redir++;
			if ((line[i] == '>' || line[i] == '<') && !all->quotes.has_quote)
				i++;
		}
		i++;
	}	
	return (n_redir);
}

t_cmd	*create_redir_list(t_cmd *node, t_all *all)
{
	int		i;
	t_redir	*temp;

	i = 0;
	node->n_redir = number_of_redirs(node->line, all);
	while (node->n_redir)
	{
		temp = lst_new_redir(file_name(node->line, all), redir_type(node->line, all));
		if (temp == NULL)
			free_lists_and_line(all);
		lst_add_back_redir(&node->redir, temp);
		node->line = clean_line_redir(node->line, all);
		node->n_redir--;
	}
	return (node);
}


char	*join_line_without_redir(char *line, char *before)
{		
	char	*new_line;

	new_line = NULL;
	line++;
	if (*line == '>' || *line == '<')
		line++;
	while (ft_is_space(*line))
		line++;
	while (!ft_is_space(*line) && *line != '\0' && *line != '<' && *line != '>')
		line++;
	new_line = ft_strjoin(before, line, 0, 0);
	return (new_line);
}

char	*clean_line_redir(char *line, t_all *all)
{
	int		i;
	char	*before;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') && !all->quotes.has_quote)
		{
			before = ft_substr(line, 0, i);
			new_line =join_line_without_redir(line + i, before);
			break ;
		}
		i++;
	}
	if (new_line)
		return (new_line);
	return (line);
}
