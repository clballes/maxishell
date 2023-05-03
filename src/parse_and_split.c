/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:14:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/03 13:56:01 by albagarc         ###   ########.fr       */
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
	while (s[count])
	{
		if (s[count] != c && ((s[count + 1] == c) || s[count + 1] == '\0')&& !is_inside_quotting(s,all,count))
			n_word++;
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
		if (count > 0 && s[count] != c && s[count -1] == c /*&& !is_inside_quotting(s,all,count)*/)
			start = count;
		printf("esta dentro:%c : %d\n",s[count],is_inside_quotting(s,all,count));
		if ((s[count] != c && ((s[count + 1] == c) || s[count + 1] == '\0'))&& !is_inside_quotting(s,all,count))
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

char	**ft_split_tokens(char const *s, char c, t_all *all)
{
	char	**result;

	result = malloc(sizeof(char *) * (ft_count_words(s, c, all) + 1));
	if (!result)
		return (NULL);
	result = ft_findposition_cutstring(s, c, result, all);
	return (result);
}
