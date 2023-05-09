/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:06:12 by clballes          #+#    #+#             */
/*   Updated: 2023/05/08 13:35:16 by albagarc         ###   ########.fr       */
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


typedef struct s_cmd 
{
    char		*cmd;
    // t_token *args;
    char		**args;
    char		*line;
    int			n_args;
	int			flag;
	int			equal; //para saber si hay iguales dentr del export
	bool	double_quote;
	bool	single_quote;
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
	char			*name;
	char			*content;
	int				concatenate;
	int				print; //para saber si se ha de printar la variable en el env o export 
	struct s_env	*temporal; //para saber la ultima osicion del env y enlazar el siguiente nodo de la lista
	struct s_env	*next;
	struct s_env	*previous;
	char			*current_cd;
	char			*new_cd;
}					t_env;

typedef struct s_all
{
	t_quo 	quotes;
    t_cmd 	*node;
	t_env	*list_env;
    char 	**env;
    char 	*all_line;
	int		exit;
    int 	n_pipes;
}       			t_all;


//line
void	exec_cmd(t_all *all);
//free
void	lstfree(t_cmd **lst);
void	lstfree_env(t_env **lst);
void	free_arr(char **array);
//utils list
t_cmd	*lst_new(char *comand);
t_cmd	*lst_last(t_cmd **lst);
int		lst_size(t_cmd *lst);
void	lst_add_back(t_cmd **first, t_cmd *new_el);
t_env	*lst_new_env(char *name, char *content);
void	lst_add_back_env(t_env **first, t_env *new_el);
t_env	*lst_last_env(t_env *lst);
void	init_struct(t_all *all);
void	env_list(t_all *all);

#endif