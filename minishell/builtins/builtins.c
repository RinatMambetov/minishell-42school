/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:36 by cluco             #+#    #+#             */
/*   Updated: 2022/04/16 20:50:39 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	ft_isbuiltin(char **cmd)
{
	if (!ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "cd")
		|| !ft_strcmp(cmd[0], "pwd")
		|| !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

void
	ft_run_builtin(char **cmd, t_cmd *c)
{
	if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, c);
	if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, c);
	if (!ft_strcmp(cmd[0], "env"))
		ft_env(cmd, c);
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd, c);
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
}
