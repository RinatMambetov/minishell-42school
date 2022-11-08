/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:35:09 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 12:09:40 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_print_env(char **env)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_arrlen(env);
	while (i < env_len)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}

void
	ft_env(char **args, t_cmd *c)
{
	g_exit_status = EXIT_SUCCESS;
	if (args[1])
	{
		g_exit_status = EXIT_FAILURE;
		ft_putendl_fd("minishell: env: too many arguments", 2);
	}
	else
		ft_print_env(c->e);
}
