/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:52:20 by albagarc          #+#    #+#             */
/*   Updated: 2023/06/07 10:40:50 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

t_redir		*lst_new_redir(char *file_name, int redir);
t_redir		*lst_last_redir(t_redir **lst);
void		lst_add_back_redir(t_redir **first, t_redir *new_el);
t_cmd 		*create_redir_list(t_cmd *node, t_all *all);
#endif