/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:59:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/08 13:30:41 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/parsing.h"
// #include "../inc/minishell.h"

// int dolar_exp_len(char *token)
// {
// 	int i;

// 	i = 0;
// 	while (token[i])
// 	{
// 		if ((token[i] >= 'a' && token[i] <= 'z') || (token[i] >= 'A' && token[i] <= 'Z') || token[i] == '_')
// 			i++;
// 		else
// 			break;
// 	}
// 	return (i);
// }

// char *dolar_exp(char *token, int index)
// {
// 	int len;
// 	char *search_env;
// 	// char puntero en el que si tenemos $USER guardamos USER;

// 	len = dolar_exp_len(token);
// 	// para hacer el len del USER para el malloc hacemos el dolar_exp_len
// 	search_env = ft_calloc(len, sizeof(char)); // FREEEEE
// 	while (len)
// 	{
// 		search_env[index] = token[index];
// 		len--;
// 	}
// 	printf("%s",search_env);
// 	return (search_env);
// }

// // Ya tenemos los argumentos guardados pero con comillas y sin hacer expansiones
// void final_tokens(t_all *all)
// {
// 	int i;
// 	int j;

// 	i = 1;
// 	j = 0;
// 	while (all->node->args[i])
// 	{
// 		if (all->node->args[i][j] == '\"' && !is_in_quottes(all->node->args[i], all, i))
// 		{
// 			all->node->double_quote = true;
// 			// all->node->args[i]++;
// 			j++;
// 		}
// 		if (all->node->args[i][j] == '\'' && !is_in_quottes(all->node->args[i], all, i))
// 		{
// 			all->node->single_quote = true;
// 			// all->node->args[i]++;
// 			j++;
// 		}
// 		if (all->node->args[i][j] == '$')
// 		{
// 			// all->node->args[i]++;
// 			j++;
// 			dolar_exp(all->node->args[i], j);
// 		}
// 		i++;
// 	}
// }
