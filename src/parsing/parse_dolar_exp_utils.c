/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 07:38:31 by codespace         #+#    #+#             */
/*   Updated: 2023/05/15 19:39:39 by codespace        ###   ########.fr       */
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
	result = NULL;
    // variable_len = 0;
    // while(str[j])
    // { 
        // if(str[j] =='$')
        // {
			
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
    //     j++;
    // }   
    // }
    return(result);
}
char	*expand_dolar(char *str, t_all *all)
{
	char *result;
	char *aux;
	char *before;
	char *after;
	int 	j;
    char quo;
	j = 0;
	result = NULL;
    all->quotes.found = '\0';
	while(str[j] != '\0')
	{
        quo = type_of_quottes(str, all , j);
        printf("[%c]\n", quo);
		if((str[j]== '$' && !is_in_quottes(str, all , j)) || (str[j]== '$' && quo =='\"' ) )
		{
			before = ft_substr(str, 0, j);
			aux = manage_dolar(ft_strdup(str + j), all);
			after = ft_strdup(str + j + len_search_value(str + j )+ 1);
			printf("before$:%s, aux$:%s, after$:%s\n", before, aux, after);
			result = ft_strjoin(before, aux);
            printf("result:%s\n",result);
			str = ft_strjoin(result, after);
            j = -1;
		}
		j++;
	}
	// if(result)
	// 	return(result);
	return (str);
}



// int	how_many_quottes(char *s)
// {
// 	int i;
// 	int count_quo;
	
// 	i = 0;
// 	count_quo = 0;
// 	while(s[i]!= '\0')
// 	{
// 		if(s[i] == '\"' || s[i] == '\'')
// 		{
// 			count_quo++;	
// 		}
// 		i++;
// 	}
// 	return (count_quo);
// }

// int	*array_printable_quotte(char *s, t_all*all)
// {
// 	int i;
// 	int *print_quo;
// 	int number_of_quottes;
// 	int j;
	
// 	i = 0;
// 	j = 0;
// 	number_of_quottes = how_many_quottes(s);
// 	print_quo = ft_calloc(number_of_quottes, sizeof(int));
// 	if(!print_quo)
// 		return NULL;//habra que poner error de malloc
// 	while (s[i] != '\0')
// 	{
// 		if(s[i] == '\"' || s[i] == '\'')
// 		{
// 			if(is_in_quottes(s,all, i))
// 			{
// 				print_quo[j] = 1;
// 				j++;
// 			}
// 			else
// 			{
// 				print_quo[j] = 0;
// 				j++;
// 			}
// 		}
// 		i++;
				
// 	}
// 	return(print_quo);
// }
//NO ESTA BIEN
// int	is_printable_quotte(int	*arr)
// {
// 	int *first;
	
// 	first = arr;
// 	arr++;
// 	return(*first);
// }