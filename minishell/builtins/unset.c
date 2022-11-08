/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:36:21 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 12:12:03 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **
	ft_strdup2_del(char **arr, int del_pos, t_cmd *c)
{
	int		i;
	int		j;
	int		len;
	char	**myarr;

	i = -1;
	j = -1;
	len = ft_arrlen(arr);
	myarr = malloc(sizeof(char *) * len);
	if (!myarr)
		free_all(c, "178940", "Error unset");
	while (++i < len)
	{
		j++;
		if (i == del_pos)
			j--;
		else
		{
			myarr[j] = ft_strdup(arr[i]);
			if (!myarr[j])
				return (NULL);
		}
	}
	myarr[j + 1] = NULL;
	return (myarr);
}

char **
	ft_del_env(char **env, char *elem, t_cmd *c)
{
	int		i;
	int		env_len;
	int		elem_len;
	char	**temp;

	i = 0;
	env_len = ft_arrlen(env);
	elem_len = ft_strlen(elem);
	while (i < env_len)
	{
		if (!ft_strncmp(env[i], elem, elem_len)
			&& (env[i][elem_len] == '=' || env[i][elem_len] == '\0'))
		{
			temp = env;
			env = ft_strdup2_del(env, i, c);
			ft_free_arr(temp);
			break ;
		}
		i++;
	}
	return (env);
}

char **
	ft_del_envs(char **argv, char **env, t_cmd *c)
{
	int		i;
	int		argv_len;

	i = 0;
	argv_len = ft_arrlen(argv) - 1;
	while (i < argv_len)
	{
		env = ft_del_env(env, argv[i + 1], c);
		i++;
	}
	return (env);
}

void
	ft_unset(char **args, t_cmd *c)
{
	char	**myenv;

	g_exit_status = EXIT_SUCCESS;
	if (!args[1])
		return ;
	else
	{
		myenv = ft_strdup2(c->e);
		if (!myenv)
			free_all(c, "178940", "Error unset");
		myenv = ft_del_envs(args, myenv, c);
		if (!myenv)
			free_all(c, "178940", "Error unset");
		ft_free_arr(c->e);
		c->e = myenv;
	}
}
