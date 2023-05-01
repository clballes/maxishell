/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:57:30 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/01 16:46:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H


int clean_all_line(char *all_line, t_quo *quotes);
char *content_list(char * line, bool init, t_all *all);
// int clean_all_line(char *all_line);
#endif