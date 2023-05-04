/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:53:21 by clballes          #+#    #+#             */
/*   Updated: 2023/04/26 12:53:22 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	exec_echo(t_cmd *builtins);
void	exec_env(t_env **list_env);
void	env_list(t_all *all);
int     exec_pwd(void);
void    exec_exit(t_all *all);
void	swap(t_env **temp);

//export funtions
void	exec_export(t_all *all);
int		check_equal(t_cmd *node, t_all *all);
int		ft_prohibited(char c, int j, int flag, int concat);
void	check_arg(t_all *all);
void	change_var_list(char *content, t_env *temp);
#endif