/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:51:54 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/23 15:27:55 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/redirections.h"
#include "../inc/parsing.h"

int	identify_redir(char a, char b)
{
	int	redir;

	if (a == '>')
	{
		if (a == b)
			redir = OUT_APPEND;
		else
			redir = OUT_TRUNCATED;
	}
	if (a == '<')
	{
		if (a == b)
			redir = HDOC;
		else
			redir = INPUT;
	}
	return (redir);
}

int	redir_type(char *line, t_all *all)
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

char	*file_name(char *line, t_all *all)
{
	int		i;
	int		start;
	char	*file_name;

	i = -1;
	while (line[++i] != '\0')
	{
		if ((line[i] == '>' || line[i] == '<') && !is_in_quottes(line, all, i))
		{	
			i++;
			if ((line[i] == '>' || line[i] == '<') && line[i] != '\0')
				i++;
			while (ft_is_space(line[i]) && line[i] != '\0')
				i++;
			start = i;
			while ((!ft_is_space(line[i]) && line[i] != '\0' \
				&& line[i] != '<' && line[i] != '>' ) || (ft_is_space(line[i]) \
					&& is_in_quottes(line, all, i)))
				i++;
			file_name = ft_substr(line, start, i - start);
			return (file_name);
		}
	}
	return (NULL);
}

int	number_of_redirs(char *line, t_all *all)
{
	int	i;
	int	n_redir;

	i = 0;
	n_redir = 0;
	while (line[i])
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
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

int	write_err(t_all *all, int j)
{
	all->exit = 1;
	if (j == 1)
		write_dyn_err \
			("msh: &: Permission denied", &all->node->redir->file_name[0]);
	else if (j == 2)
		write_dyn_err \
			("msh: &: No such file or directory", \
				&all->node->redir->file_name[0]);
	else
		write_dyn_err \
			("msh: &: Is a directory", &all->node->redir->file_name[0]);
	exit(all->exit);
}
