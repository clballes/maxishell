/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:59:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/09 21:07:10 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

int dolar_exp_len(char *token)
{
	int i;

	i = 0;
	// NUMEROS
	while (token[i])
	{
		// if(token[0] >= '0' && token[i] <= '9' )
		if ((token[i] >= 'a' && token[i] <= 'z') || (token[i] >= 'A' && token[i] <= 'Z') || token[i] == '_' /* || (token[i] >= '0' && token[i] <= '9')*/)
			i++;
		else
			break;
	}
	printf("iii:%d\n", i);
	return (i);
}

char *dolar_search_value(char *token)
{
	int len;
	char *search_env;
	// char puntero en el que si tenemos $USER guardamos USER;
	int i;
	i = 0;
	len = dolar_exp_len(token);
	printf("len:%d\n", len);
	// para hacer el len del USER para el malloc hacemos el dolar_exp_len
	search_env = ft_calloc(len + 1, sizeof(char)); // FREEEEE
	if (!search_env)
		return NULL;
	while (len)
	{
		search_env[i] = token[i];
		len--;
		i++;
	}
	search_env[dolar_exp_len(token)] = '\0';
	printf("search_Env:%s\n", search_env);
	return (search_env);
}

char *env_search(t_env *env, char *search_value)
{

	t_env *first_node; // guardamos aqui el primer elemento de la lista
	first_node = env;
	while (env) // recorremos la lista
	{
		
		if (ft_strncmp(env->name, search_value, ft_strlen(search_value)) == 0)
		{
			free(search_value);
			return (env->content);
		}
		env = env->next;
		// printf("p1:%p p2:%p \n", first_node, env);
	}
	env = first_node;
	free(search_value);
	return (NULL);
	// return(0);
}

// Ya tenemos los argumentos guardados pero con comillas y sin hacer expansiones
void clean_tokens(t_all *all, t_cmd *node)
{
	int i;
	int j;
	char *search_value;	  // se hace el malloc en dolar_search_value y se libera en env_search
	char *expanded_value; // es el puntero que apunta a la lista de env asi que no lo liberamos.
	char *before_dolar;
	char *result;

	i = 1;
	j = 0;
	if (!node->args[1])
		return;
	while (node->args[i])
	{
		j= 0;
		while (node->args[i][j] != '\0')
		{
			
			if (node->args[i][j] == '\"' && !is_in_quottes(node->args[i], all, i))
			{
				node->double_quote = true;
				// node->args[i]++;
				j++;
			}
			if (node->args[i][j] == '\'' && !is_in_quottes(node->args[i], all, i))
			{
				node->single_quote = true;
				// node->args[i]++;
				j++;
			}
			if (node->args[i][j] == '$')
			{
				if (j != 0)
					before_dolar = ft_substr(node->args[i], 0, j);
				j++;
				search_value = dolar_search_value(node->args[i] + j);
				ft_strlen(search_values)//QUIERO LA longitud de USER para avanzar el puntero
				expanded_value = env_search(all->list_env, search_value);
				
				ft_strjoin(expandex_value, )// quiero poner que me anada lo que sobra
				if(expanded_value)
				{
					result = ft_strjoin(before_dolar, expanded_value);
					// node->args[i] = result;//habria que hacer free de result????Creo que no porque liberamos el dela lista
				}
				// i = 0;
				j = 0;
				printf("contenido:%s \n", expanded_value);
				printf("result:%s\n",  result);
				
			}
			printf("que hay una vez pasado el dolar%c\n",node->args[i][j]);
			j++;
		}
		// exit(0);
		// if (node->args[i][j] == '$' && )
		i++;
	}
}

int final_tokens_in_nodes(t_all *all)
{
	t_cmd *first_node; // guardamos aqui el primer elemento de la lista
	first_node = all->node;
	while (all->node) // recorremos la lista
	{
		printf("arg[0]%s\n", all->node->args[0]);
		printf("arg[1]%s\n", all->node->args[1]);
		printf("arg[2]%s\n", all->node->args[2]);
		clean_tokens(all, all->node);

		all->node = all->node->next;
		// printf("p1:%p p2:%p \n", first_node, all->node);
	}
	all->node = first_node;
	return (0);
}