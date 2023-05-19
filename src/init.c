/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:28:57 by albagarc          #+#    #+#             */
/*   Updated: 2023/05/19 11:39:13 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdbool.h>
void	init_struct(t_all *all)
{
	all->quotes.has_quote = 0;
	all->quotes.found = '\0';
	all->exit = 0;
	all->bar = 0;
	all->absolute = 0;
	// all->all_line = NULL;
	env_list(all);
}