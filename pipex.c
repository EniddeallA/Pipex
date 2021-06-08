/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:15:48 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/08 09:40:35 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
    ** USAGE :  ./pipex file1 cmd1 cmd2 file2
*/


void    pipex(int fd1, char *cmd1, char *cmd2, int fd2)
{
    
}


int     main(int argc, char *argv[])
{
    int fd1;
    int fd2;

    if (argc == 5)
    {
        if ((fd1 = open(argv[1], O_RDWR)) < 0 || (fd2 = open(argv[4], O_RDWR)) < 0)
            error_handler("File doesn't exist.");
        pipex(fd1, argv[2], argv[3], fd2);
        close(fd1);
        close(fd2);
    }
    else
        error_handler("USAGE: '> ./pipex file1 cmd1 cmd2 file2'.");
    return (0);
}