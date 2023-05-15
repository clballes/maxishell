/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:57:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/15 16:42:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "minishell.h"

int 	valid_clean_line(char *all_line, t_all *all);
char 	*content_list(char * line, bool init, t_all *all);
int 	is_in_quottes( char *line, t_all *all, int i);
// void	divide_in_tokens(t_all *all);
char	**ft_split_tokens(char  *s, char c, t_all *all);
char	*ft_strtrim_free_s1(char *s1, char const *set);
int		double_pointer_len(char **args);
int 	final_tokens_in_nodes(t_all *all);
int		ft_is_space(char c);
char    *extract_in_quottes(char* str, int index, char quo, t_cmd *node);
char    *manage_dolar(char *str, t_all *all);
int     dolar_exp_len(char *token);
char    *dolar_search_value(char *token);
char    *search_in_env(t_env *env, char *search_value);
// int     has_dolar(char *s);
char	*expand_dolar(char *str, t_all *all);
int		len_search_value(char *str);
// int clean_all_line(char *all_line);
#endif