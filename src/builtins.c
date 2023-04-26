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

int    exec_option(char *args)
{
    int i;

    i = 2;
    while(args[i] && args[i] != 32)
    {
        if (args[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}


void    exec_echo(t_cmd *builtins)
{
    int i;
    int res;
    int len;

    i = 1;
    res = 0;
    while (ft_strncmp(builtins->args[i], "-n", 2) == 0)
    {
        if(exec_option(builtins->args[i]) != 1)
        {
            res = 1;
            i++;
        }
        else
            break;
    }
    while (builtins->args[i])
    {
        len = ft_strlen(builtins->args[i]);
        write(1, builtins->args[i] , len);
        if (builtins->args[i + 1] != NULL )
            write(1, " " , 1);
        i++;
    }
    if (res == 0)
        write(1, "\n", 1);
}