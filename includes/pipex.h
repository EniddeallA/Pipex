/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 09:16:04 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/13 08:48:18 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	**cmd1_args;
	char	*cmd2;
	char	**cmd2_args;
	char	**env;
	int		fd[2];
}				t_pipex;

/*
	** LIBFT
*/

int		ft_strlen(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s1);

/*
	** PIPEX
*/

void	pipex(t_pipex *p);
void	execute_cmd1(t_pipex *p);
void	execute_cmd2(t_pipex *p);
void	check_pipex(t_pipex **p);

/*
	** PIPEX_UTILS
*/

void	get_cmd_path(t_pipex **p, int cmd_n);
char	*get_new_path(char **env);
int		concatenate_paths(char *path, char **cmd_n, char *arg);
void	error_handler(char *str, int err);

#endif