/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:06:12 by clballes          #+#    #+#             */
/*   Updated: 2023/04/28 13:52:02 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
#include <stdbool.h>


// desgrana cada linea de comando en tokens
typedef struct s_token{
    char *tkn_content;
    bool single_quote;
    bool double_quote;
    struct s_token *next;
}t_token;
//Guarda cada linea de comando 
typedef struct s_cmd 
{
    char *cmd;
    t_token *args;
    // char **args;
    char   *line;
    int    n_args;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_quo
{
	char 	found;
	int		index;
	int		has_quote;
} t_quo;

typedef struct s_env
{
    char *name;
    char *content;
    struct s_env *next;
}       t_env;

typedef struct s_all
{
	t_quo quotes;
    t_cmd *node;
    char **env;
    char *all_line;
}       t_all;

//line
void    exec_cmd();
t_cmd	*lst_new(char* comand);
t_cmd	*lst_last(t_cmd *lst);
void	lst_add_back(t_cmd **first, t_cmd *new_el);
void	lstfree(t_cmd **lst);

#endif