/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:06:12 by clballes          #+#    #+#             */
/*   Updated: 2023/05/19 16:05:00 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>


typedef struct s_cmd 
{
    char		*cmd;
    // t_token *args;
    char		**args;
    char		*line;
    int			n_args;
	int			flag;
	int			equal; //para saber si hay iguales dentr del export
	int			fd[2];	
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
	int				print_oldpwd; //saber cuando printar le old pwd
}					t_env;

typedef struct s_all
{
	t_quo 	quotes;
    t_cmd 	*node;
	t_env	*list_env;
    char 	**env;
    char 	*all_line;
	int		exit;
	char	minishell; //flag para minishell dentro de minishell
	int		cd; //para saber si nos movemos
	int		absolute; //to kno if its a absolute path 
	int		bar; // esta es la cd //
    int 	n_pipes;
}       			t_all;

//line
void	exec_cmd(t_all *all);
//free
void	lstfree_cmd(t_cmd **lst);
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
char	*ft_strjoin_path(char const *s1, char const *s2);
char	*get_line(void);

//path
int		search_path(t_all *all);
void		fork_function(t_all *all, char *new_path);
void	free_lists_and_line(t_all *all);

<<<<<<< HEAD
// pipes
void	pipes(t_all *all);
=======
>>>>>>> heredoc
#endif