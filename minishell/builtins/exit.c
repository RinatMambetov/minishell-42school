/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:18:23 by greita            #+#    #+#             */
/*   Updated: 2022/04/16 20:50:30 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	ft_check_exit_arg(char *arg)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(arg);
	if (arg[0] != '-' && !ft_isdigit(arg[0]))
		return (1);
	while (i < len)
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int
	ft_get_exit_status(char *arg)
{
	int	result;

	result = ft_atoi(arg);
	if (result < 0)
		return (256 - (-result % 256));
	else
		return (result % 256);
}

void
	ft_exit(char **args)
{
	g_exit_status = EXIT_SUCCESS;
	printf("exit\n");
	if (ft_arrlen(args) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_exit_status = EXIT_FAILURE;
	}
	else if (ft_arrlen(args) == 2)
	{
		if (!ft_check_exit_arg(args[1]))
			g_exit_status = ft_get_exit_status(args[1]);
		else
		{
			g_exit_status = 255;
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
		}
	}
	exit(g_exit_status);
}
