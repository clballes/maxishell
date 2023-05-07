/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:49:53 by clballes          #+#    #+#             */
/*   Updated: 2023/05/02 09:49:55 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

void    change_env(t_all *all)
{
    t_env *temp;
    temp = all->list_env;
    while(temp)
    {
        if(ft_strncmp(temp->name, "PWD",ft_strlen(temp->name)) == 0)
            temp->content = all->list_env->new_cd;
        if(ft_strncmp(temp->name, "OLDPWD",ft_strlen(temp->name)) == 0)
            temp->content = all->list_env->current_cd;
        temp = temp->next;
    }
}

int    exec_cd(t_all *all)
{
    all->list_env->current_cd = getcwd(NULL, 0);
    // printf("Current working directory is now: %s\n", all->list_env->current_cd);
    if (all->node->args[1])
        chdir(all->node->args[1]);
    else
        chdir(getenv("HOME"));
    all->list_env->new_cd = getcwd(NULL, 0);
    printf("%s\n", all->list_env->new_cd);
    change_env(all);
    // if (chdir("/home/user/Desktop") == -1) {
    //     perror("chdir failed");
    //     return 1;
    // }
    return 0;
}