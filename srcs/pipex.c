/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:15:48 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/16 11:23:15 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd1(t_pipex *p)
{
	dup2(p->fd1, 0);
	dup2(p->fd[1], 1);
	close(p->fd[1]);
	close(p->fd[0]);
	execve(p->cmd1, p->cmd1_args, p->env);
}

void	execute_cmd2(t_pipex *p)
{
	dup2(p->fd2, 1);
	dup2(p->fd[0], 0);
	close(p->fd[0]);
	execve(p->cmd2, p->cmd2_args, p->env);
}

void	pipex(t_pipex *p)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_handler("Fork(): Something went wrong.", 1);
	else if (pid == 0)
		execute_cmd1(p);
	close(p->fd[1]);
	pid = fork();
	if (pid == 0)
		execute_cmd2(p);
	close(p->fd[0]);
	waitpid(p->fd[0], &(p->fd_status), 0);
	waitpid(p->fd[1], &(p->fd_status), 0);
}

void	check_pipex(t_pipex **p)
{
	if ((*p)->fd1 < 0)
		error_handler(strerror(errno), 0);
	if ((*p)->fd2 < 0)
		error_handler(strerror(errno), 0);
	(*p)->cmd1_args = ft_split((*p)->cmd1, ' ');
	get_cmd_path(p, 1);
	(*p)->cmd2_args = ft_split((*p)->cmd2, ' ');
	get_cmd_path(p, 2);
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	*p;

	p = NULL;
	if (argc == 5)
	{
		p = (t_pipex *)malloc(sizeof(t_pipex));
		if (pipe(p->fd) == -1)
			error_handler("Pipe(): Something went wrong.", 1);
		p->fd1 = open(argv[1], O_RDONLY);
		p->fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		p->env = env;
		p->cmd1 = argv[2];
		p->cmd2 = argv[3];
		check_pipex(&p);
		pipex(p);
		close(p->fd1);
		close(p->fd2);
	}
	else
		error_handler("USAGE: '> ./pipex file1 cmd1 cmd2 file2'.", 1);
	if (WIFEXITED(p->fd_status))
		return (WEXITSTATUS(p->fd_status));
	return (0);
}
