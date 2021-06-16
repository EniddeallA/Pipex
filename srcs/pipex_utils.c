/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 06:06:59 by akhalid           #+#    #+#             */
/*   Updated: 2021/06/16 02:31:05 by eniddealla       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_new_path(char **env)
{
	int		i;
	char	*new_path;

	i = 0;
	new_path = NULL;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			new_path = ft_strdup(ft_strrchr(env[i], '=') + 1);
			break ;
		}
		i++;
	}
	return (new_path);
}
int	concatenate_paths(char *path, char **cmd_n, char *arg)
{
	char	*cmd;
	char	*tmp;

	cmd = ft_strjoin(path, "/");
	tmp = cmd;
	cmd = ft_strjoin(cmd, arg);
	free(tmp);
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
	free(new_path);
	i = 0;
	while (split_path[i])
		free(split_path[i++]);
	free(split_path);
	if (!check)
		error_handler("Command not found.", 127);
}

void	error_handler(char *str, int err)
{
	write(1, "Error: ", 8);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(err);
}
