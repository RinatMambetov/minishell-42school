/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:13:36 by greita            #+#    #+#             */
/*   Updated: 2022/04/16 17:55:23 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **
	ft_strdup2_slash(char **arr, t_cmd *c)
{
	int		i;
	int		len;
	char	**myarr;

	i = 0;
	len = ft_arrlen(arr);
	myarr = malloc(sizeof(char *) * (len + 1));
	if (!myarr)
		free_all(c, "178940", "Error cd");
	while (i < len)
	{
		if (!i)
			myarr[i] = ft_strdup(arr[i]);
		else
			myarr[i] = ft_strjoin("/", arr[i]);
		if (!myarr[i])
			return (NULL);
		i++;
	}
	myarr[i] = NULL;
	return (myarr);
}

int
	ft_cd_all(char *arg, t_cmd *c, char *start_path)
{
	int		i;
	int		root;
	int		paths_amount;
	char	**paths;

	ft_check_slash(arg[0], &i, &root);
	paths = ft_split(arg, '/');
	paths = ft_strdup2_slash(paths, c);
	if (!paths)
		free_all(c, "178940", "Error cd");
	paths_amount = ft_arrlen(paths);
	if (!ft_go_start(paths[0], root, start_path))
	{
		while (i < paths_amount)
		{
			if (ft_cd_path(paths[i], c))
				return (1);
			i++;
		}
	}
	else
		free_all(c, "178940", "Error cd");
	ft_free_arr(paths);
	return (0);
}

void
	ft_go_oldpwd(t_cmd *c, char *start_path)
{
	char	*oldpwd_path;

	oldpwd_path = ft_get_oldpwd(c->e);
	if (ft_check_oldpwd(oldpwd_path))
		return ;
	else
		ft_export_start_path(c, start_path);
	if (chdir(oldpwd_path) == -1)
		ft_putendl_fd("minishell: cd: No such file or directory", 2);
}

void
	ft_go_home(t_cmd *c, char *start_path)
{
	char	*home_path;

	ft_export_start_path(c, start_path);
	home_path = ft_get_home(c->e);
	if (ft_check_home_path(home_path))
		return ;
	if (chdir(home_path) == -1)
		ft_putendl_fd("minishell: cd: No such file or directory", 2);
}

void
	ft_cd(char **args, t_cmd *c)
{
	char	start_path[PATH_LENGTH];

	g_exit_status = EXIT_SUCCESS;
	if (!getcwd(start_path, sizeof(start_path)))
		ft_putendl_fd("minishell: cd: error getcwd", 2);
	if (!args[1])
		ft_go_home(c, start_path);
	else if (!ft_strcmp(args[1], "-"))
		ft_go_oldpwd(c, start_path);
	else
	{
		ft_export_start_path(c, start_path);
		if (ft_cd_all(args[1], c, start_path))
		{
			g_exit_status = EXIT_FAILURE;
			if (chdir(start_path) == -1)
				ft_putendl_fd("minishell: cd: No such file or directory", 2);
		}
	}
}
