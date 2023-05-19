/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:59:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/19 18:35:35 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"
// Nos devuelve la longitud de la variable a buscar en el env
// Ej:$USER nos devuelve 4
// cuenta solo los valores validos para una variable que son letras
// barra baja _
// numeros si no estan en la primera posicion


int dolar_exp_len(char *token)
{
	int i;

	i = 0;
	// NUMEROS
	while (token[i])
	{
		// if(token[0] >= '0' && token[0] <= '9' )
		// 	return(i);	
		if ((token[i] >= 'a' && token[i] <= 'z') \
			|| (token[i] >= 'A' && token[i] <= 'Z') \
			|| token[i] == '_' || (token[i] >= '0' && token[i] <= '9'))
			i++;
		else
			break;
	}
	return (i);
}



// char puntero en el que si tenemos $USER guardamos USER;
char *dolar_search_value(char *token)
{
	int len;
	char *search_env;
	int i;
	
	i = 0;
	len = dolar_exp_len(token);
	search_env = ft_calloc(len + 1, sizeof(char)); // FREEEEE y proteccion
	if (!search_env)
		return NULL;
	while (len)
	{
		search_env[i] = token[i];
		len--;
		i++;
	}
	search_env[dolar_exp_len(token)] = '\0';
	return (search_env);
}

char *search_in_env(t_env *env, char *search_value)
{

	t_env *first_node; // guardamos aqui el primer elemento de la lista
	first_node = env;
	while (env && ft_strlen(search_value)) // recorremos la lista
	{
		
		if (ft_strncmp(env->name, search_value, ft_strlen(search_value)+1) == 0)
		{
			// free(search_value);
			return (ft_strdup(env->content)); ///ft_strdup(env->content); y liberarla
		}
		env = env->next;
	}
	env = first_node;
	// free(search_value);
	return (ft_strdup(""));
	// return(0);
}


int len_search_value(char *str)
{
	char *search_value;
	int variable_len;
	
	variable_len = 0;
	search_value = dolar_search_value(str + 1);
	variable_len = ft_strlen(search_value);	
	free(search_value);
	return(variable_len);										

}

void clean_tokens(t_all *all, t_cmd *node)
{
	int i;
	char *result;
	(void)all;
	i = 0;

	// if (!node->args[1])
	// 	return;
	while (node->args[i])
	{

		result = expand_dolar(ft_strdup(node->args[i]), all);
		//SPLIT result en tokens again
		// printf("resultado del dolar%s\n", result);
		result = manage_quottes(result);
		free(node->args[i]);
		node->args[i] = result;																
		// printf("NODE_ARGS:%p la i es:%d\n", node->args[i], i);
		i++;
	}
}

int final_tokens_in_nodes(t_all *all)
{
	t_cmd *first_node; // guardamos aqui el primer elemento de la lista
	first_node = all->node;
	while (all->node) // recorremos la lista
	{
		clean_tokens(all, all->node);
		lst_last(&all->node)->cmd = lst_last(&all->node)->args[0];
		all->node = all->node->next;
	}
	all->node = first_node;
	return (0);
}