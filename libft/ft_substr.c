/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:49:59 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/09 19:01:40 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	size_t			i;
	unsigned int	cont;

	cont = 0;
	i = ft_strlen(s) - start;
	if (len >= i && start < ft_strlen(s))
		len = i;
	else if (start >= ft_strlen(s))
		len = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	while (cont < len)
	{
		new_str[cont] = s[start];
		cont++;
		start++;
	}
	new_str[cont] = '\0';
	return (new_str);
}
