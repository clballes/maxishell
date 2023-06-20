/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:57:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/20 20:05:09 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "minishell.h"

int 	valid_clean_line(char *all_line, t_all *all);
void	create_list_pipes(char *all_line, t_all *all);
char 	*content_list(char * line, bool init, t_all *all);
int 	is_in_quottes( char *line, t_all *all, int i);
char	**ft_split_tokens(char  *s, char c, t_all *all);
char	*ft_strtrim_free_s1(char *s1, char const *set);
int 	final_tokens_in_nodes(t_all *all);
int		ft_is_space(char c);
int     dolar_exp_len(char *token);
char    *dolar_search_value(char *token, t_all *all);
char    *search_in_env(t_env *env, char *search_value);
char	*expand_dolar(char *str, t_all *all);
int		len_search_value(char *str, t_all *all);
char	type_of_quottes(char *line, t_all *all, int i);
char    *extract_in_quottes(char* str, char quo);
char 	*manage_quottes(char* str);
int		syntax_redir_ok(char *line, t_all *all);
int		is_valid_char(char c);
char	*manage_dolar_exit(char *str, t_all *all);
char	*manage_dolar_env(char *str, t_all *all);
char	*manage_dolar_number(char *str);
int		syntax_pipes_ok(char *line, t_all *all);
#endif