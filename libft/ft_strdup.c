/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:44:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/23 10:49:11 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = ft_strlen(s1) + 1;
	ptr = malloc (sizeof(char) * i);
	if (ptr != NULL)
	{
		ft_memcpy(ptr, s1, i);
		return (ptr);
	}
	return (0);
}
