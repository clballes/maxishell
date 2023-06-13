/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:26:39 by clballes          #+#    #+#             */
/*   Updated: 2023/06/13 16:18:14 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

//child heredoc
// char	*child_heredoc()
// {
// 	char *line;
// 	char *prompt;
// 	prompt = "> ";
// 	line = readline(prompt);
// 	if (!line)
// 	{
// 		if (isatty(STDIN_FILENO))
// 			write(2, "exit\n", 6);
// 		exit(0);
// 	}
// 	return (line);
// }

// //fork heredoc
// char	*fork_heredoc()
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid < 0)
// 		printf("ERROR EN EL FORK DE HEREDOCC\n");
// 	if (pid == 0)
// 		child_heredoc();
// 	return (NULL);
// }

//check line for heredoc
// void	heredoc(t_all *all, char *delimitator, int *fd)
// {
// 	(void)all;
// 	// printf("delimitator is : %s\n", delimitator);
// 	int	fd[2];
// 	char *line;
	
// 	if(pipe(fd)<0)
// 	{
// 		printf("tirar error\n");	
// 	}	

// 	// close(fd[0]);
// 	while(1)
// 	{
// 		line = readline("> ");
// 		if(ft_strncmp(line, delimitator, ft_strlen(delimitator)) != 0)
// 			write(fd[1], &line, ft_strlen(line));
// 		else 
// 			break ;	
// 		free(line);
// 	}
// 	close(fd[1]);
// 	exec_cmd(all, all->node);
	
// }



