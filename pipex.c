/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:15:48 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/13 06:05:49 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
    ** USAGE :  ./pipex file1 cmd1 cmd2 file2
*/


void execute_cmd1(t_pipex *p)
{
    printf("child1\n");
    dup2(p->fd1, 0);
    dup2(p->fd[1], 1);
    close(p->fd[0]);
    execve(p->cmd1, p->cmd1_args, p->env);
    error_handler("Something went wrong executing cmd1.");
}

void execute_cmd2(t_pipex *p)
{
    printf("child2\n");
    dup2(p->fd2, 1);
    dup2(p->fd[0], 0);
    close(p->fd[1]);
    execve(p->cmd2, p->cmd2_args, p->env);
    error_handler("Something went wrong executing cmd2.");
}

void    pipex(t_pipex *p)
{
    int child1;
    int child2;
    int child1_status;
    int child2_status;

    if ((child1 = fork()) == -1)
        error_handler("Something went wrong while creating child1");
    else if (child1 == 0)
    {
        execute_cmd1(p);
        if ((child2 = fork()) == -1)
            error_handler("Something went wrong creating child2");
    }
    else
        execute_cmd2(p);
}

char    *get_new_path(char **env)
{
    int i;
    char *new_path;

    i = 0;
    while(env[i])
    {
        if (!ft_strncmp("PATH", env[i], 4))
        {
            new_path = (char *)malloc(sizeof(char) * ft_strlen(ft_strrchr(env[i], '=')));
            new_path = ft_strrchr(env[i], '=') + 1;
            break;
        }
        i++;
    }
    return (new_path);
}

int     concatenate_paths(char *path, char **cmd_n, char *arg)
{
    char *cmd;

    cmd = ft_strjoin(path, "/");
    cmd = ft_strjoin(cmd, arg);
    if (open(cmd, O_RDONLY) > 0)
    {
        *cmd_n = ft_strdup(cmd);
        free(cmd);
        return (1);
    }
    free(cmd);
    return (0);
}

void get_cmd_path(t_pipex **p, int cmd_n)
{
    int i;
    char *new_path;
    char **split_path;
    int check;

    check = 0;
    new_path = get_new_path((*p)->env);
    split_path = ft_split(new_path, ':');
    i = 0;
    while (split_path[i] && !check)
    {
        if (cmd_n == 1)
            check = concatenate_paths(split_path[i], &(*p)->cmd1, (*p)->cmd1_args[0]);
        else if (cmd_n == 2)
            check = concatenate_paths(split_path[i], &(*p)->cmd2, (*p)->cmd2_args[0]);
        i++;
    }
    i = 0;
    while (split_path[i])
        free(split_path[i++]);
    free(split_path);
    if (!check)
        error_handler("Command not found.");
}

void check_pipex(t_pipex **p)
{
     if ((*p)->fd1 < 0)
        error_handler("Infile can't be found or created.");
     if ((*p)->fd2 < 0)
        error_handler("Outfile can't be found or created.");
    (*p)->cmd1_args = ft_split((*p)->cmd1, ' ');
    get_cmd_path(p, 1);
    (*p)->cmd2_args = ft_split((*p)->cmd2, ' ');
    get_cmd_path(p, 2);
}

int     main(int argc, char *argv[], char **env)
{
    t_pipex *p;

    if (argc == 5)
    {
        p = (t_pipex *)malloc(sizeof(t_pipex));
        if (pipe(p->fd) == -1)
            error_handler("Something went wrong using Pipe.");
        p->fd1 = open(argv[1], O_RDONLY);
        p->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        p->env = env;
        p->cmd1 = argv[2];
        p->cmd2 = argv[3];
        check_pipex(&p);
        pipex(p);
        close(p->fd1);
        close(p->fd2);
    }
    else
        error_handler("USAGE: '> ./pipex file1 cmd1 cmd2 file2'.");
    
    return (0);
}