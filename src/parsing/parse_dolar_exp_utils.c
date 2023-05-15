/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 07:38:31 by codespace         #+#    #+#             */
/*   Updated: 2023/05/15 05:53:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"


int len_in_quottes(char *str, char quo)
{
	int i;

	i = 1;
	while(str[i]!= quo)
	{
		i++;
	}	
	return (i);
}

char    *extract_in_quottes(char* str, int index, char quo, t_cmd *node)
{
    
    int i;
    int len_in_quo;
    char * in_quottes;
    char *result;

    i = 0;
    
    
    if(quo == '\'')
        node->single_quote = true;
    else
        node->double_quote = true;
    while(str[i])
    {
        if(str[i] == quo)
        {
            len_in_quo = len_in_quottes(str + index +1, quo);
            printf("len:%d\n",len_in_quo);
            in_quottes = ft_substr(str , index + 1, len_in_quo);
            result = in_quottes;
            // free (before_quottes);
            // free(in_quottes); 
        }
        i++;
    }
    return(result); 
}

char    *manage_dolar(char *str, t_all *all)
{
    // char *before_dolar;
    int     j;
    char    *search_value;
    char    *expanded_value;
    // int 	variable_len;
    char    *result;
    
    
    j = 0;
    // variable_len = 0;
    // while(str[j])
    // {
        if(str[j] =='$')
        {
            // before_dolar = ft_substr(str, 0, j);
            // printf("before$$:%s\n", before_dolar);
            
            // if(ft_is_space(str[j + 1]) || str[j + 1] == '\0')
            // {
            //     str = ft_strjoin( before_dolar, ft_strdup("$"));
            //     return (str);
                
            // }
            // j++;
            // if (str[j] >= '0' && str[j] <= '9')
            // {
            //     j++;
            //     result = ft_strjoin(before_dolar, str + j);		
            // }
            // else if (str[j] == '?')
            // {
            //     j++;
            //     result = ft_strjoin(before_dolar, ft_itoa(all->exit));		
            // }
            // else
            // {
                search_value = dolar_search_value(str + j + 1);						
                expanded_value = search_in_env(all->list_env, search_value); 
                result = expanded_value;
            // }
        }   
        j++;
    // }
    return(result);
}

