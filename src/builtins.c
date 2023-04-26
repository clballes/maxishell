/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:38:25 by clballes          #+#    #+#             */
/*   Updated: 2023/04/26 11:38:28 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/builtins.h"

int    exec_option(t_cmd *builtins)
{
    int i;
    int j;

    j = 2;
    i = 1;
    while(builtins->args[i])
    {
        while(builtins->args[i][j] && builtins->args[i][j] != 32)
        {
            if (builtins->args[i][j] != 'n')
                return (1);
            j++;
        }
        i++;
    }
    // if (ft_strncmp(builtins->args[i], "-n", 2) == 0)
    //     exec_option(builtins);
    // // printf("surtooo\n");
    return (0);
}


void    exec_echo(t_cmd *builtins)
{
    int i;
    int len;

    i = 1;
    if (ft_strncmp(builtins->args[i], "-n", 2) == 0)
        if(exec_option(builtins) != 1)
            i++;
    while (builtins->args[i])
    {
        len = ft_strlen(builtins->args[i]);
        write(1, builtins->args[i] , len);
        if (builtins->args[i + 1] != NULL )
            write(1, " " , 1);
        i++;
    }
    if (ft_strncmp(builtins->args[1], "-n", 2) != 0)
        write(1, "\n", 1);
}