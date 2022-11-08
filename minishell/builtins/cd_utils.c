/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:13:59 by greita            #+#    #+#             */
/*   Updated: 2022/04/16 17:55:35 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_export_start_path(t_cmd *c, char *start_path)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("export");
	args[1] = ft_strjoin("OLDPWD=", start_path);
	args[2] = NULL;
	if (!args || !args[0] || !args[1])
		free_all(c, "178940", "Error cd");
	ft_export(args, c);
	ft_free_arr(args);
}

char *
	ft_level_up(char *path)
{
	char	*new_path;
	char	*last_slash;

	if (!ft_strcmp(path, "/"))
		new_path = ft_strdup("/");
	else
	{
		last_slash = ft_strrchr(path, '/');
		new_path = ft_substr(path, 0, last_slash - path);
	}
	return (new_path);
}

int
	ft_cd_path(char *path, t_cmd *c)
{
	char	current_path[PATH_LENGTH];
	char	*new_path;

	if (!getcwd(current_path, sizeof(current_path)))
	{
		ft_putendl_fd("minishell: cd: error getcwd", 2);
		return (1);
	}
	if (!ft_strcmp(path, "/."))
		new_path = ft_strdup(current_path);
	else if (!ft_strcmp(path, "/.."))
		new_path = ft_level_up(current_path);
	else
		new_path = ft_strjoin(current_path, path);
	if (!new_path)
		free_all(c, "178940", "Error cd");
	if (chdir(new_path) == -1)
	{
		ft_putendl_fd("minishell: cd: No such file or directory", 2);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

void
	ft_go_root(void)
{
	if (chdir("/") == -1)
		ft_putendl_fd("minishell: cd: No such file or directory", 2);
}

int
	ft_go_start(char *path, int root, char *start_path)
{
	char	*new_path;

	if (root)
		ft_go_root();
	else if (!ft_strcmp(path, ".."))
	{
		new_path = ft_level_up(path);
		if (!new_path)
			return (1);
		if (chdir(new_path) == -1)
			ft_putendl_fd("minishell: cd: No such file or directory", 2);
		free(new_path);
	}
	else if (path[0] != '.' && ft_strlen(path) != 1)
	{
		new_path = ft_strjoin(start_path, "/");
		new_path = ft_strjoin(new_path, path);
		if (!new_path)
			return (1);
		if (chdir(new_path) == -1)
			ft_putendl_fd("minishell: cd: No such file or directory", 2);
		free(new_path);
	}
	return (0);
}
