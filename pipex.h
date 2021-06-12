/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:16:04 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/13 00:32:02 by eniddealla       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct  s_pipex
{
    int fd1;
    int fd2;
    char *cmd1;
    char *cmd2;
    char **env;
    int fd[2];
}               t_pipex;


/*
    ** PIPEX_UTILS
*/

int     ft_strlen(char *s);
int     ft_atoi(char *str);
void    error_handler(char *str);

/*
    ** PIPEX
*/

void pipex(t_pipex *p);


#endif