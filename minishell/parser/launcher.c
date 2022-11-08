/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:52:38 by cluco             #+#    #+#             */
/*   Updated: 2022/04/14 12:57:02 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_exit_status(int exit_status)
{
	if (exit_status == 256)
		g_exit_status = 1;
	if (exit_status == 512)
		g_exit_status = 127;
}

static int	ft_run_not_builtin(t_cmd *c, char **ex)
{
	pid_t	pid;

	ft_run_signals(2, c);
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
		run_execve(c, ex);
	else
	{
		if (waitpid(pid, &g_exit_status, 0) < 0)
			return (1);
		ft_check_exit_status(g_exit_status);
	}
	return (0);
}

static void	launch_single_cmd(t_cmd *c)
{
	int		i;
	char	**ex;

	ex = redirects_cut_off(c->cmd[0], c);
	if (!ex)
	{
		g_exit_status = EXIT_FAILURE;
		perror("redirect");
		return ;
	}
	if (ft_isbuiltin(ex) == 0)
	{
		if (ft_run_not_builtin(c, ex))
			return ;
	}
	else
		ft_run_builtin(ex, c);
	set_std_fd(c);
	i = 0;
	while (ex[i] != NULL)
		free(ex[i++]);
	free(ex);
}

static void	launch_multiple(t_cmd *c)
{
	int	i;

	i = -1;
	while (c->count > ++i)
	{
		if (c->count > 1 && i < c->count - 1 && c->type[i] == '|')
		{
			if (i % 2 == 0 && (pipe(c->fd1)))
				free_all(c, "19840", "pipe 1");
			if (i % 2 == 1 && (pipe(c->fd2)))
				free_all(c, "19840", "pipe 2");
		}
		run_cmd(c, i);
	}
}

void	launcher(t_cmd *c)
{
	if (c->count == 1)
		launch_single_cmd(c);
	else
		launch_multiple(c);
	ft_run_signals(1, c);
	unlink("clucoheredoc");
}
