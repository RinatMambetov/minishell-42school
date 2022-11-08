/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:38:04 by greita            #+#    #+#             */
/*   Updated: 2022/04/07 11:55:38 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	ft_check_export_arg(char *arg)
{
	if (ft_isalpha(arg[0]) || arg[0] == '_')
		return (0);
	return (1);
}

char *
	ft_get_name(char *arg)
{
	int		name_len;
	char	*name;

	if (!ft_strchr(arg, '='))
		name_len = ft_strlen(arg);
	else
		name_len = ft_strchr(arg, '=') - arg;
	name = ft_substr(arg, 0, name_len);
	return (name);
}

int
	ft_get_elem_id(char *elem, char **env)
{
	int	i;
	int	elem_len;
	int	env_len;

	i = 0;
	elem_len = ft_strlen(elem);
	env_len = ft_arrlen(env);
	while (i < env_len)
	{
		if (!ft_strncmp(env[i], elem, elem_len)
			&& (env[i][elem_len] == '=' || env[i][elem_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char **
	ft_strdup2_replace(char **arr, char *str, int id)
{
	int		i;
	int		len;
	char	**myarr;

	i = 0;
	len = ft_arrlen(arr);
	myarr = malloc(sizeof(char *) * (len + 1));
	if (!myarr)
		return (NULL);
	while (i < len)
	{
		if (i == id)
			myarr[i] = ft_strdup(str);
		else
			myarr[i] = ft_strdup(arr[i]);
		i++;
	}
	myarr[i] = NULL;
	return (myarr);
}

char **
	ft_add_env(char *name, char *arg, char **env)
{
	int		id;
	char	*str;
	char	**new_env;
	char	*value;

	if (ft_strlen(name) == ft_strlen(arg))
		new_env = ft_strdup2_add(env, name);
	else
	{
		value = arg + ft_strlen(name) + 1;
		str = ft_strjoin2(name, value);
		id = ft_get_elem_id(name, env);
		if (id >= 0)
			new_env = ft_strdup2_replace(env, str, id);
		else
			new_env = ft_strdup2_add(env, str);
		free(str);
	}
	return (new_env);
}
