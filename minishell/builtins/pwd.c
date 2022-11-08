/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 21:31:39 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 12:11:52 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_pwd(void)
{
	char	path[PATH_LENGTH];

	g_exit_status = EXIT_SUCCESS;
	if (!getcwd(path, sizeof(path)))
	{
		g_exit_status = EXIT_FAILURE;
		ft_putendl_fd("minishell: pwd: error getcwd", 2);
		return ;
	}
	printf("%s\n", path);
}
