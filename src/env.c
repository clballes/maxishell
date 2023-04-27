/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:35:30 by clballes          #+#    #+#             */
/*   Updated: 2023/04/27 11:35:31 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

// void    get_env()
// {
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
//    printf("ROOT : %s\n", getenv("ROOT"));
//    printf("USER : %s\n", getenv("USER"));
//    printf("PWD : %s\n", getenv("PWD"));

// }

void    env_list(t_all *all)
{
   t_env *list_env;
   t_env *temp;
   char *pos;
   int   i;

   i = 0;
   printf("el %s\n", all->env[0]);
   while(all->env[i])
   {
      printf("holaaaaaa\n");
      // pos = ft_strchr(all->env[i], '=');
      // pos = ft_strtrim(pos, "=");
      // temp->content = pos;
      temp = lst_new_env(NULL, NULL);
      lst_add_back(&list_env, temp);
      temp = temp->next;
      i++;
      // printf("la psition es %s\n", temp->content);
      // // temp = lst_new();
      // free(pos);
      // temp = temp->next;
      i++;
   }
}
