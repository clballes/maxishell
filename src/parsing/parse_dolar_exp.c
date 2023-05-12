/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:59:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/12 15:05:55 by albagarc         ###   ########.fr       */
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
	// if(!len)
	// 	return(NULL);
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
	printf("search_Env:%s\n", search_env);
	return (search_env);
}

char *search_in_env(t_env *env, char *search_value)
{

	t_env *first_node; // guardamos aqui el primer elemento de la lista
	first_node = env;
	while (env && ft_strlen(search_value)) // recorremos la lista
	{
		
		if (ft_strncmp(env->name, search_value, ft_strlen(search_value)) == 0)
		{
			free(search_value);
			return (env->content); ///ft_strdup(env->content); y liberarla
		}
		env = env->next;
		// printf("p1:%p p2:%p \n", first_node, env);
	}
	env = first_node;
	free(search_value);
	return (ft_strdup(""));
	// return(0);
}
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
// Ya tenemos los argumentos guardados pero con comillas y sin hacer expansiones
void clean_tokens(t_all *all, t_cmd *node)
{
	int i;
	int j;
	char *search_value;	  // se hace el malloc en dolar_search_value y se libera en env_search
	char *expanded_value; // es el puntero que apunta a la lista de env asi que no lo liberamos.
	char *before_dolar;
	char *result;
	int	variable_len;
	char *before_quottes;
	int  quo_len;
	char *in_quottes;//malloc con el substring
	
	i = 0;
	j = 0;
	if (!node->args[1])
		return;
	while (node->args[i])
	{
		j= 0;
		while (node->args[i][j] != '\0')
		{
			//tengo que poner de alguna manera el node->double_quote a 0
			// printf("caracter:%c is in quotes?:%d single:%d double:%d\n", node->args[i][j], is_in_quottes(node->args[i], all, i), node->single_quote, node->double_quote );
			// if(!is_in_quottes(node->args[i], all, i))
			// {
			// 	node->double_quote = false;
			// 	node->single_quote = false;
			// }
			printf("valor [%c] esta en comillas o no:%d\n",node->args[i][j],is_in_quottes(node->args[i], all, j));
			if (node->args[i][j] == '\"' && is_in_quottes(node->args[i], all, j))
			{
				before_quottes = ft_substr(node->args[i], 0, j);
				// calculamos la len de lo que hay en quottes
				node->double_quote = true;
				j++;
				quo_len = len_in_quottes(node->args[i] + j, '\"');
				in_quottes = ft_substr(node->args[i], j, quo_len);
				result = ft_strjoin(before_quottes,in_quottes);
				printf("len entre comillas:%d estring entre comillas:%s\n",quo_len, in_quottes);
			}
			if (node->args[i][j] == '\'' && is_in_quottes(node->args[i], all, j))
			{
				before_quottes = ft_substr(node->args[i], 0, j);
				node->single_quote = true;
				j++;
				// in_quottes = ft_substr(node->args[i], j, j);
			}
			if (node->double_quote && !is_in_quottes(node->args[i], all, j))
			{
				node->double_quote = false;
				j++;
			}
			if (node->single_quote && !is_in_quottes(node->args[i], all, j))
			{
				node->single_quote = false;
				j++;
			}
			if (node->args[i][j] == '$' && node->single_quote == false)
			{
				before_dolar = ft_substr(node->args[i], 0, j);									//si no hay nada porque pasamos 0 y 0 nose devuelve un string vacio
				if(ft_is_space(node->args[i][j + 1]) || node->args[i][j + 1] == '\0')
				{
					node->args[i] = ft_strjoin( before_dolar, ft_strdup("$"));
					return ;
				}
				j++;
				if (node->args[i][j] >= '0' && node->args[i][j] <= '9')
				{
					j++;
					result = ft_strjoin(before_dolar, node->args[i] + j);		
				}
				else if (node->args[i][j] == '?')
				{
					j++;
					result = ft_strjoin(before_dolar, ft_itoa(all->exit));		
				}
				else
				{
					search_value = dolar_search_value(node->args[i] + j);
					printf("search_value:%s\n", search_value); 							//search value es USER
					variable_len = ft_strlen(search_value);											//QUIERO LA longitud de USER para avanzar el puntero
					expanded_value = search_in_env(all->list_env, search_value); 
					printf("expanded value: %s\n", expanded_value);							//Busca el search_value (USER) en la lista de env y devuelve albagarc
					expanded_value = ft_strjoin(expanded_value, node->args[i] + j + variable_len);
				
					result = ft_strjoin(before_dolar, expanded_value);//hay que liberar dentro del join	
				}
				node->args[i] = result;																//habria que hacer free de result????Creo que no porque liberamos el dela lista
				printf("guardamos[%s]\n", node->args[i]);
			}
			j++;
		}
		i++;
	}
}

int final_tokens_in_nodes(t_all *all)
{
	t_cmd *first_node; // guardamos aqui el primer elemento de la lista
	first_node = all->node;
	while (all->node) // recorremos la lista
	{
		// printf("arg[0]%s\n", all->node->args[0]);
		// printf("arg[1]%s\n", all->node->args[1]);
		// printf("arg[2]%s\n", all->node->args[2]);
		clean_tokens(all, all->node);
		lst_last(&all->node)->cmd = lst_last(&all->node)->args[0];
		all->node = all->node->next;
		// printf("p1:%p p2:%p \n", first_node, all->node);
	}
	all->node = first_node;
	return (0);
}