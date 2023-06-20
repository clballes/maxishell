/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 08:44:23 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/20 15:38:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int free_s1, int free_s2)
{
	size_t	total;
	char	*str;
	
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(total, 1);
	if (!str)
		return (NULL);
	ft_strlcat(str, s1, total);
	ft_strlcat(str, s2, total);
	if(free_s1)
		free(s1);
	if(free_s2)
		free(s2);
	return (str);
}