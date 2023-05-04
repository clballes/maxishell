/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:57:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/04 18:32:20 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H


int 	valid_line(char *all_line, t_all *all);
char 	*content_list(char * line, bool init, t_all *all);
int 	is_in_quottes( char *line, t_all *all, int i);
void	divide_in_tokens(t_all *all);
char	**ft_split_tokens(char  *s, char c, t_all *all);
char	*ft_strtrim_free_s1(char *s1, char const *set);
// int clean_all_line(char *all_line);
#endif