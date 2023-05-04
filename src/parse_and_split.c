/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:14:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/04 15:54:05 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

static int	ft_count_words(char *s, char c, t_all *all)
{
	int	count;
	int	n_word;

	count = 0;
	n_word = 0;
	while (s[count])
	{
		if ((s[count] != c && (s[count + 1] == c) \
		&& !is_in_quottes(s, all, count + 1)) || s[count + 1] == '\0')
		{
			n_word++;
		}
		count++;
	}
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

static char	**ft_extract_token(char *s, char c, char **result, t_all *all)
{
	int		n_word;
	int		i;
	int		start;

	n_word = 0;
	i = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			start = i;
		if (i > 0 && s[i] == c && s[i +1] != c && !is_in_quottes(s, all, i))
			start = i + 1;
		if (s[i] != c && ((s[i + 1] == c && !is_in_quottes(s, all, i + 1)) \
			|| s[i + 1] == '\0'))
		{
			result[n_word] = ft_substr(s, start, i - start + 1);
			if (!result[n_word])
				return (ft_free(result, n_word));
			n_word++;
		}
		i++;
	}
	result[n_word] = NULL;
	return (result);
}

char	*ft_strtrim_free_s1(char *s1, char const *set)
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
	free(s1);
	return (new);
}

char	**ft_split_tokens(char *s, char c, t_all *all)
{
	char	**result;

	result = malloc(sizeof(char *) * (ft_count_words(s, c, all) + 1));
	if (!result)
		return (NULL);
	result = ft_extract_token(s, c, result, all);
	return (result);
}
