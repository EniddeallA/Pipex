/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:15:48 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/13 00:44:00 by eniddealla       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
    ** USAGE :  ./pipex file1 cmd1 cmd2 file2
*/



void    pipex(t_pipex *p)
{
    int child1;
    int child2;
    int *child1_status;
    int *child2_status;

    if ((child1 = fork()) == -1)
        error_handler("Something went wrong while creating child1");
    else if (child1 == 0)
    {
        execute_cmd1(p);
        if ((child2 = fork()) == -1)
            error_handler("Something went wrong creating child2");
    }
    else if(child2 == 0)
        execute_cmd2(p);
    else
    {
        wait_pid(child1, &child1_status, WCONTINUED);
        wait_pid(child2, &child2_status, WCONTINUED);
    }
}

int     main(int argc, char *argv[], char **env)
{
    t_pipex *p;

    if (argc == 5)
    {
        p = (t_pipex *)malloc(sizeof(t_pipex));
        if (pipe(p->fd) == - 1)
            error_handler("Something went wrong using pipe()");
        p->fd1 = open(argv[1], O_RDONLY);
        p->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        p->env = env;
        p->cmd1 = argv[2];
        p->cmd2 = argv[3];
        pipex(p);
    }
    else
        error_handler("USAGE: '> ./pipex file1 cmd1 cmd2 file2'.");
    return (0);
}