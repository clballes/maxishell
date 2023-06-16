/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:05 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/11 17:49:30 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/redirections.h"
#include "../inc/parsing.h"

char	*clean_line_redir(char *line, t_all *all);

t_cmd	*create_redir_list(t_cmd *node, t_all *all)
{
	int		i;
	t_redir	*temp;

	i = 0;
	node->n_redir = number_of_redirs(node->line, all);
	while (node->n_redir)
	{
		temp = lst_new_redir(file_name(node->line, all), \
			redir_type(node->line, all));
		if (temp == NULL)
			free_lists_and_line(all);
		// manage_quottes(temp->file_name);
		// printf("file_name es %s\n",temp->file_name);
		lst_add_back_redir(&node->redir, temp);
		free(node->line);
		node->line = clean_line_redir(node->line, all);
		node->n_redir--;
	}

	return (node);
}

// char	*join_line_without_redir(char *line, char *before)
// {		
// 	char	*new_line;

// 	new_line = NULL;
// 	line++;
// 	if (*line == '>' || *line == '<')
// 		line++;
// 	while (ft_is_space(*line))
// 		line++;
// 	while ((!ft_is_space(*line) && *line != '\0' && *line != '<' && *line != '>') /*|| (ft_is_space(*line) && is_in_quottes(line, all, i))*/)
// 		line++;
// 	new_line = ft_strjoin(before, ft_strdup(line), 1, 1);
// 	return (new_line);
// }



char	*join_line_without_redir(char *line, char *before, t_all *all)
{		
	char	*new_line;
	int i;

	i = 0;
	new_line = NULL;
	i++;
	if (line[i] == '>' || line[i] == '<')
		i++;
	while (ft_is_space(line[i]))
		i++;
	while ((!ft_is_space(line[i]) && line[i] != '\0' && line[i] != '<' && \
		line[i] != '>') || (ft_is_space(line[i]) && is_in_quottes(line, all, i)))
		i++;
	new_line = ft_strjoin(before, ft_strdup(line + i), 1, 1);
	// printf("new_line is %s\n",new_line);
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
			new_line = join_line_without_redir(line + i, before, all);
			new_line = ft_strtrim_free_s1(new_line, " ");
			break ;
		}
		i++;
	}
	if (new_line)
		return (new_line);
	return (line);
}

