/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:52:20 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/15 15:44:52 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

t_redir		*lst_new_redir(char *file_name, int redir);
t_redir		*lst_last_redir(t_redir **lst);
int			lst_size_redir(t_redir **lst);
void		lst_add_back_redir(t_redir **first, t_redir *new_el);
t_cmd 		*create_redir_list(t_cmd *node, t_all *all);
int			identify_redir(char a, char b);
int			redir_type(char *line, t_all *all);
char		*file_name(char *line, t_all *all);
int			number_of_redirs(char *line, t_all *all);
int			access_path(char *filename, t_all *all, int *type); //li passem el filename
int			redir_output(t_all *all, t_redir *temp, int type);
int			redir_loop(t_cmd **node, t_all *all);
#endif