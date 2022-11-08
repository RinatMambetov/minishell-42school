/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:38:06 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 12:11:11 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_print_export(char **arr)
{
	int		i;
	int		name_len;
	char	*eq_sign;

	i = 0;
	while (arr[i])
	{
		write(1, "declare -x ", 11);
		eq_sign = ft_strchr(arr[i], '=');
		if (eq_sign)
		{
			name_len = eq_sign - arr[i];
			write(1, arr[i], name_len + 1);
			write(1, "\"", 1);
			write(1, arr[i] + name_len + 1, ft_strlen(arr[i]) - name_len - 1);
			write(1, "\"\n", 2);
		}
		else
			printf("%s\n", arr[i]);
		i++;
	}
}

void
	ft_print_error(char *arg)
{
	g_exit_status = EXIT_FAILURE;
	printf("minishell: export: `%s': not a valid identifier\n", arg);
}

char **
	ft_add_envs(char **args, char **env)
{
	int		i;
	int		argv_len;
	char	*name;
	char	**temp;

	i = -1;
	argv_len = ft_arrlen(args) - 1;
	while (++i < argv_len)
	{
		if (!ft_check_export_arg(args[i + 1]))
		{
			name = ft_get_name(args[i + 1]);
			if (!name)
				return (NULL);
			temp = env;
			env = ft_add_env(name, args[i + 1], env);
			if (!env)
				return (NULL);
			ft_free_arr(temp);
			free(name);
		}
		else
			ft_print_error(args[i + 1]);
	}
	return (env);
}

void
	ft_export(char **args, t_cmd *c)
{
	char	**myenv;

	g_exit_status = EXIT_SUCCESS;
	myenv = ft_strdup2(c->e);
	if (!myenv)
		free_all(c, "178940", "Error export");
	if (!args[1])
	{
		ft_sort_env(myenv, c);
		ft_print_export(myenv);
	}
	else
	{
		myenv = ft_add_envs(args, myenv);
		if (!myenv)
			free_all(c, "178940", "Error export");
	}
	ft_free_arr(c->e);
	c->e = myenv;
}
