/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:06:12 by clballes          #+#    #+#             */
/*   Updated: 2023/06/23 12:50:54 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include "signal.h"

//fd pipes
# define READ	0
# define WRITE	1

# define TRUE	1 
# define FALSE	0

//Redirecciones
# define OUT_TRUNCATED	1 // >
# define OUT_APPEND		2 // >>
# define INPUT				3 // <
# define HDOC			4 // <<

typedef struct s_global
{
	int	g_ctrlc;
}	t_global;

typedef struct s_redir
{
	char			*file_name;
	int				type;
	struct s_redir	*next;
}t_redir;

typedef struct s_cmd
{
	int				empty_string;
	int				n_redir;
	char			*cmd;
	char			**args;
	char			*line;
	int				keep_quottes;
	int				n_args;
	int				flag;
	int				equal;
	pid_t			pid;
	t_redir			*redir;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}t_cmd;

typedef struct s_quo
{
	char	found;
	int		index;
	int		has_quote;
}t_quo;

typedef struct s_env
{
	char			*name;
	char			*content;
	int				concatenate;
	int				print;
	struct s_env	*temporal;
	struct s_env	*next;
	struct s_env	*previous;
	char			*current_cd;
	char			*new_cd;
	int				print_oldpwd;
}					t_env;

typedef struct s_pipe
{
	int		fd[2];
	int		fd_temp;

}t_pipe;

typedef struct s_all
{
	t_quo	quotes;
	int		status;
	int		exist;
	t_cmd	*node;
	t_env	*list_env;
	char	**env;
	char	**env_array;
	char	*all_line;
	int		exit;
	int		env_i;
	int		cd;
	int		absolute;
	int		bar;
	int		n_pipes;
}t_all;

t_global	g_glbl;


//line
void	exec_cmd(t_all *all, t_cmd *temp);

//free
void	lstfree_cmd(t_cmd **lst);
void	lstfree_env(t_env **lst);
void	free_arr(char **array);
void	lstfree_redir(t_redir **lst);

//utils list
t_cmd	*lst_new(char *comand);
t_cmd	*lst_last(t_cmd **lst);
int		lst_size_env(t_env **lst);
int		lst_size(t_cmd *lst);
void	lst_add_back(t_cmd **first, t_cmd *new_el);
t_env	*lst_new_env(char *name, char *content);
void	lst_add_back_env(t_env **first, t_env *new_el);
t_env	*lst_last_env(t_env *lst);
t_all	*init_struct(t_all *all, char **env);
void	env_list(t_all *all);
char	*ft_strjoin_path(char const *s1, char const *s2);
char	*get_line(t_all *all);

//path
int		search_path(t_all *all, t_cmd *node);
void	execve_path(t_all *all, char *new_path);
void	free_lists_and_line(t_all *all);

// pipes
void	minishell_starts(t_all *all);
int		set_fd_for_pipes_father(t_cmd *node, t_pipe *pipes);
int		set_fd_for_pipes_child(t_all *all, t_pipe *pipes, t_cmd *temp);

//print functions
char	**list_to_double_pointer(t_env **list, t_all *all);
void	write_dyn_err(char *message, char *var);
void	set_term(void);
void	init_signal(int mode,  t_all *all);

//heredoc
int		is_there_heredoc(t_redir **redir);

#endif