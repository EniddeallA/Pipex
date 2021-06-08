/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:20:19 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/08 09:36:07 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int     ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

int     ft_atoi(char *str)
{
    int sign;
    int res;

    res = 0;
    sign = 1;
    while (*str == ' ' || *str == '\t')
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    if (*str < '0' || *str > '9')
        error_handler("Number contains wrong values.");
    while (*str >= '0' && *str <= '9')
        res *= 10 + *str++ - 48;
    return (res * sign);
}

void    error_handler(char *str)
{
    write(1, "Error:", 7);
    write(1, &str, ft_strlen(str));
    write(1, "\n", 1);
    exit(2);
}