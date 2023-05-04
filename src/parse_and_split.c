/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:14:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/04 13:31:29 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

static int	ft_count_words(char	const *s, char c, t_all *all)
{
	int	count;
	int	n_word;

	count = 0;
	n_word = 0;
	printf("que linea llega para contar palabras:%s que has_quotellega:%d\n", s, all->quotes.has_quote);
	while (s[count])
	{
		// printf("s[%d]:%c\n", count, s[count]);
		if ((s[count] != c && (s[count + 1] == c) && !is_inside_quotting(s,all,count + 1))|| s[count + 1] == '\0')
		{
			n_word++;
		}
		count++;
	}
	printf("n_word=%d\n",n_word);
	return (n_word);
}

static char	**ft_free(char **result, int n_word)
{
	while (n_word > 0)
	{
		n_word--;
		free(result[n_word]);
	}
	free(result);
	return (0);
}

static char	**ft_findposition_cutstring(char const *s, char c, char **result, t_all *all)
{
	int		n_word;
	int		count;
	int		start;

	n_word = 0;
	count = 0;
	while (s[count])
	{
		if (count == 0 && s[count] != c)
			start = count;
		if (count > 0 && s[count] == c && s[count +1] != c && !is_inside_quotting(s,all,count))
		{
			start = count + 1;
		 	printf("actualizando start:%c:%d\n",s[count],is_inside_quotting(s,all,count));
			
		}
		if (s[count] != c 
			&& ((s[count + 1] == c && !is_inside_quotting(s,all,count + 1))
			|| s[count + 1] == '\0'))
		{
			result[n_word] = ft_substr(s, start, count - start + 1);
			if (!result[n_word])
				return (ft_free(result, n_word));
			n_word++;
		}
		count++;
	}
	result[n_word] = NULL;
	return (result);
}

char	*ft_strtrim_free_s1(const char *s1, char const *set)
{
	char	*new;
	int		count;
	int		s1_len;

	count = 0;
	s1_len = ft_strlen(s1);
	while (s1[count] && ft_strchr(set, s1[count]))
	{
		count++;
	}
	while (*s1 && ft_strchr(set, s1[s1_len - 1]))
	{
		s1_len--;
	}
	new = ft_substr(s1, count, (s1_len - count));
	// free((char*)s1);
	return (new);
}


char	**ft_split_tokens(const char *s, char c, t_all *all)
{
	char	**result;
	all->node->line = ft_strtrim_free_s1(s, " ");
	
	result = malloc(sizeof(char *) * (ft_count_words(all->node->line, c, all) + 1));
	if (!result)
		return (NULL);
	
	result = ft_findposition_cutstring(s, c, result, all);
	// result = ft_findposition_cutstring(s, c, result, all);
	return (result);
}
