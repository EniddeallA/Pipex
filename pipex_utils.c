/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 06:06:59 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/13 06:22:56 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_new_path(char **env)
{
	int		i;
	char	*new_path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH", env[i], 4))
		{
			new_path = (char *)malloc(sizeof(char)
					* ft_strlen(ft_strrchr(env[i], '=')));
			new_path = ft_strrchr(env[i], '=') + 1;
			break ;
		}
		i++;
	}
	return (new_path);
}

int	concatenate_paths(char *path, char **cmd_n, char *arg)
{
	char	*cmd;

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

void	get_cmd_path(t_pipex **p, int cmd_n)
{
	int		i;
	char	*new_path;
	char	**split_path;
	int		check;

	check = 0;
	new_path = get_new_path((*p)->env);
	split_path = ft_split(new_path, ':');
	i = 0;
	while (split_path[i] && !check)
	{
		if (cmd_n == 1)
			check = concatenate_paths(split_path[i], &(*p)->cmd1,
					(*p)->cmd1_args[0]);
		else if (cmd_n == 2)
			check = concatenate_paths(split_path[i], &(*p)->cmd2,
					(*p)->cmd2_args[0]);
		i++;
	}
	i = 0;
	while (split_path[i])
		free(split_path[i++]);
	free(split_path);
	if (!check)
		error_handler("Command not found.");
}

void	error_handler(char *str)
{
	write(1, "Error:", 7);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(2);
}
