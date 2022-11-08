/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:05:08 by greita            #+#    #+#             */
/*   Updated: 2022/04/16 17:53:29 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_check_slash(char ch, int *i, int *root)
{
	*i = 1;
	*root = 0;
	if (ch == '/')
	{
		*i = 0;
		*root = 1;
	}
}

int
	ft_check_home_path(char *home_path)
{
	if (!home_path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

char *
	ft_get_home(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_arrlen(env);
	while (i < env_len)
	{
		if (!ft_strncmp(env[i], "HOME=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

int
	ft_check_oldpwd(char *oldpwd_path)
{
	if (!oldpwd_path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		g_exit_status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

char *
	ft_get_oldpwd(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_arrlen(env);
	while (i < env_len)
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			return (env[i] + 7);
		i++;
	}
	return (NULL);
}
