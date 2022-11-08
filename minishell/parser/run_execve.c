/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:41:55 by cluco             #+#    #+#             */
/*   Updated: 2022/03/28 23:01:49 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *there_is_path(char *s, char **dirs)
{
	int i;
	char *path;
	char *tmp;

	i = -1;
	while (dirs[++i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		free(dirs[i]);
		dirs[i] = tmp;
		path = ft_strjoin(dirs[i], s);
		if (access(path, X_OK) == 0)
		{
			i = -1;
			while (dirs[++i])
				free(dirs[i]);
			free(dirs);
			return (path);
		}
		free(path);
	}
	return (s);
}

static char *get_path(char *s, char **env)
{
	int i;
	char **tmp;
	char *dir;

	if (ft_strchr(s, '/'))
		return (s);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			tmp = ft_split(env[i], '=');
			dir = ft_strdup(tmp[1]);
			i = -1;
			while (tmp[++i])
				free(tmp[i]);
			free(tmp);
			tmp = ft_split(dir, ':');
			free(dir);
			return (there_is_path(s, tmp));
		}
	}
	return (s);
}

void run_execve(t_cmd *c, char **ex)
{
	int i;

	c->path = get_path(ex[0], c->e);
	execve(c->path, ex, c->e);
	i = 0;
	while (ex[i] != NULL)
		free(ex[i++]);
	free(ex);
	free_all(c, "198460", c->path);
	exit(0);
}
