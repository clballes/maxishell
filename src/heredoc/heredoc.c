/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:26:39 by clballes          #+#    #+#             */
/*   Updated: 2023/05/24 10:26:40 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

//child heredoc
char	*child_heredoc()
{
	char *line;
	char *prompt;
	prompt = "> ";
	line = readline(prompt);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		exit(0);
	}
	return (line);
}

//fork heredoc
char	*fork_heredoc()
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		printf("ERROR EN EL FORK DE HEREDOCC\n");
	if (pid == 0)
		child_heredoc();
	return (NULL);
}

//check line for heredoc
void	heredoc(t_all *all)
{
	int	i;

	i = 0;
	while (all->node->args)
	{
		if ((ft_strncmp(all->node->args[i], "<<", ft_strlen(all->node->args[i])) == 0)) //si trobem la direccio
		{
			// line = fork_heredoc();
			break;
		}			
		i++;
	}
}



