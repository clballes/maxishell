/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:57:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/03 12:59:56 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H


int 	clean_all_line(char *all_line, t_quo *quotes);
char 	*content_list(char * line, bool init, t_all *all);
int 	is_inside_quotting(const char *line, t_all *all, int i);
void	divide_in_tokens(t_all *all);
char	**ft_split_tokens(char const *s, char c, t_all *all);
// int clean_all_line(char *all_line);
#endif