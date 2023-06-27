/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:45:01 by clballes          #+#    #+#             */
/*   Updated: 2023/06/21 18:27:04 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

void	heredoc(t_all *all, char *delimitator, int *fd_in);
void	heredoc_fork(t_cmd *temp, t_all *all, t_pipe *pipes);
#endif
