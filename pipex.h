/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:16:04 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/13 03:01:55 by eniddealla       ###   ########.fr       */
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
    char **cmd1_args;
    char *cmd2;
    char **cmd2_args;
    char **env;
    int fd[2];
}               t_pipex;


/*
    ** PIPEX_UTILS
*/

int     ft_strlen(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void    error_handler(char *str);
char    **ft_split(char const *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);

/*
    ** PIPEX
*/

void pipex(t_pipex *p);
void execute_cmd1(t_pipex *p);
void execute_cmd2(t_pipex *p);
void check_pipex(t_pipex **p);

#endif