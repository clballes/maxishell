/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_env_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:50:40 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/20 18:34:53 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing.h"
#include "../inc/minishell.h"

// Nos devuelve la longitud de la variable a buscar en el env
// Ej:$USER nos devuelve 4
// cuenta solo los valores validos para una variable que son letras
// barra baja _
// numeros si no estan en la primera posicion
int	dolar_exp_len(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{	
		if ((token[i] >= 'a' && token[i] <= 'z') \
			|| (token[i] >= 'A' && token[i] <= 'Z') \
			|| token[i] == '_' || (token[i] >= '0' && token[i] <= '9'))
			i++;
		else
			break ;
	}
	return (i);
}

// char puntero en el que si tenemos $USER guardamos USER;
char	*dolar_search_value(char *token, t_all *all)
{
	int		len;
	char	*search_env;
	int		i;

	i = 0;
	len = dolar_exp_len(token);
	search_env = ft_calloc(len + 1, sizeof(char));
	if (!search_env)
		free_lists_and_line(all);
	while (len)
	{
		search_env[i] = token[i];
		len--;
		i++;
	}
	search_env[dolar_exp_len(token)] = '\0';
	return (search_env);
}

char	*search_in_env(t_env *env, char *search_value)
{
	t_env	*first_node;

	first_node = env;
	while (env && ft_strlen(search_value))
	{	
		if (ft_strncmp(env->name, search_value, \
			ft_strlen(search_value) + 1) == 0)
		{
			return (ft_strdup(env->content));
		}
		env = env->next;
	}
	env = first_node;
	return (ft_strdup(""));
}

int	len_search_value(char *str, t_all *all)
{
	char	*search_value;
	int		variable_len;

	variable_len = 0;
	search_value = dolar_search_value(str + 1, all);
	variable_len = ft_strlen(search_value);
	free(search_value);
	return (variable_len);
}
