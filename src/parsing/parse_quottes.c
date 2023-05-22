/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quottes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:28:11 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/22 14:41:42 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

int len_in_quottes(char *str, char quo)
{
	int i;

	i = 0;
	while(str[i]!= quo && str[i] != '\0')
	{

		// printf("entra?????\n");
		i++;
	}	
	return (i);
}

char    *extract_in_quottes(char* str, char quo)
{
    
    int i;
    int len_in_quo;
    char * in_quottes;

    i = 0;
    
    in_quottes = NULL;
    while(str[i])
    {
        if(str[i] == quo)
        {
            len_in_quo = len_in_quottes(str + i + 1, quo);
            in_quottes = ft_substr(str , i + 1, len_in_quo);
			break;
        }
        i++;
    }
    return(in_quottes); 
}

char	*quottes_processed(char *str, char quo, int j)
{
	char *result;
	char *aux;
	char *before;
		
	before = ft_substr(str, 0, j);
	aux = extract_in_quottes(str + j, quo);
	result = ft_strjoin(before, aux, 1, 1);
	return(result);
}

char 	*manage_quottes(char* str)
{
	char *before_and_quo;
	char *after;
	char quo;
	int 	j;
	
	j=0;
	before_and_quo = NULL;	
	while(str[j])
    {
		if(str[j] == '\"' || str[j] == '\'')
        { 
			if(str[j] == '\"')
				quo = '\"';
			if(str[j] == '\'')
				quo = '\'';
			before_and_quo = quottes_processed(str, quo, j);
			after = ft_strdup(str + j + len_in_quottes(str + j + 1, quo) + 2);
			free(str);
			str = ft_strjoin(before_and_quo, after, 1, 1);
			j = ft_strlen(before_and_quo) - 1;
		}	
		j++;
	}
	return(str);
}