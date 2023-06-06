/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:47:05 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/06 19:50:32 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/redirections.h"
#include "../inc/parsing.h"




int	redir_type(char *line,  t_all *all)
{
	int	i;
	int redir;
	i = 0;
	redir = 0;
	all->quotes.has_quote = 0;
	while (line[i] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
		if (line[i] == '>' && !all->quotes.has_quote)
		{	
			if(line[i + 1] == line[i])    
				redir = OUTPUT_APPEND;
			redir = OUTPUT_TRUNCATED;
			break ;
		}
		if (line[i] == '<' && !all->quotes.has_quote)
		{	
			if(line[i + 1] == line[i])
				redir = HEREDOC;
			redir = INPUT;
			break ;
		}
		i++;
	}
	printf("type redir es : %d\n", redir);
	return(redir);
}

char *file_name(char *line, t_all *all)
{
	int	i;
	int start;
	char *file_name;

	i = 0;
	all->quotes.has_quote = 0;
	while (line[i] != '\0')
	{
		all->quotes.has_quote = is_in_quottes(line, all, i);
		if ((line[i] == '>' || line[i] == '<')&& !all->quotes.has_quote)
		{	
			i++;
			if (line[i] == '>' || line[i] == '<')
				i++;
			while(ft_is_space(line[i]))
				i++;
			start = i;
			while(!ft_is_space(line[i]))
				i++;
			file_name = ft_substr(line, start, i - start + 1);
			printf("file_name : %s\n",file_name);
			return(file_name);//FREEEEEEE
		}
		i++;
	}
	return (NULL);
}

