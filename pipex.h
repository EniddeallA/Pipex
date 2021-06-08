/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:16:04 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/08 09:40:01 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>

/*
    ** PIPEX_UTILS
*/

int     ft_strlen(char *s);
int     ft_atoi(char *str);
void    error_handler(char *str);

/*
    ** PIPEX
*/

void pipex(int fd1, char *cmd1, char *cmd2, int fd2);


#endif