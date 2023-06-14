/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:48:35 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/14 15:18:17 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if(s1 == NULL && s2 != NULL)
		return(-1);
	if(s1 != NULL && s2 == NULL)
		return(1);
	if(s1 == NULL && s2 == NULL)
		return(0);
	i = 0;
	while (i < (n - 1) && (s1[i] == s2[i]) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	if (n == 0)
		return (0);
	return (((unsigned char *)s1)[i] -((unsigned char *) s2)[i]);
}
