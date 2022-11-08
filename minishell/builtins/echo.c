/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:22:23 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 20:13:32 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	ft_print_echo(char **args, int n_option)
{
	int	i;
	int	len;

	i = 1 + n_option;
	len = ft_arrlen(args);
	while (i < len)
	{
		printf("%s", args[i]);
		if (i != len - 1)
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
}

static int
	ft_get_n_options(char **args)
{
	int	i;
	int	n_options;

	i = 1;
	n_options = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "-n"))
			n_options++;
		else
			break ;
		i++;
	}
	return (n_options);
}

void
	ft_echo(char **args)
{
	int	n_options;

	g_exit_status = EXIT_SUCCESS;
	n_options = ft_get_n_options(args);
	ft_print_echo(args, n_options);
}
