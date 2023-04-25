/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:06:12 by clballes          #+#    #+#             */
/*   Updated: 2023/04/25 16:59:02 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include "../libft/libft.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


typedef struct s_cmd 
{
    char *cmd;
    char **args;
    char **env;
    int    n_args;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_pipes
{
    t_cmd *node;
}       t_pipes;

//line
void    exec_cmd();

t_cmd	*lst_new(char* comand);
t_cmd	*lst_last(t_cmd *lst);
void	lst_add_back(t_cmd **first, t_cmd *new_el);


#endif