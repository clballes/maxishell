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
void	exec_env(t_all *all);
int		exec_pwd(t_all *all);
int		exec_cd(t_all *all);
void	exec_exit(t_all *all);
void	swap(t_env **temp);
void	exec_unset(t_all *all);
void	error_msg(t_all *all); //free malloc perq faig un join

//export funtions
void	exec_export(t_all *all);
void	sort_list(t_env **list_env);
void	print_list(t_all *all);
int		ft_prohibited(char c, int j, int flag, int concat);
int     check_arg(t_all *all, char *arg, int j);
void	change_var_list(char *content, t_env *temp);
char	*extract_var_value(char *arg);
char	*extract_var_name(char *arg);

//path
char	*path_direction(t_all *all, char *direction);
void	change_env(t_all *all);
int     lst_size_env(t_env **lst);

#endif