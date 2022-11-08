/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:36:18 by cluco             #+#    #+#             */
/*   Updated: 2022/04/14 12:47:22 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_pipe2(t_cmd *c, int i)
{
	if (i < c->count - 1 && i % 2 == 0 && c->type[i] == '|')
	{
		if (close(c->fd1[0]) == -1)
			free_all(c, "19840", "close unused pipe 3");
		if (dup2(c->fd1[1], STDOUT_FILENO) == -1)
			free_all(c, "19840", "dup2 pipe 3");
		if (close(c->fd1[1]) == -1)
			free_all(c, "19840", "close pipe 3");
	}
	if (i < c->count - 1 && i % 2 == 1 && c->type[i] == '|')
	{
		if (close(c->fd2[0]) == -1)
			free_all(c, "19840", "close unused pipe 4");
		if (dup2(c->fd2[1], STDOUT_FILENO) == -1)
			free_all(c, "19840", "dup2 4");
		if (close(c->fd2[1]) == -1)
			free_all(c, "19840", "close pipe 4");
	}
}

static void	handle_pipe(t_cmd *c, int i)
{
	if (i > 0 && i % 2 == 0 && c->type[i - 1] == '|')
	{
		if (close(c->fd2[1]) == -1)
			free_all(c, "19840", "close unused pipe 1");
		if (dup2(c->fd2[0], STDIN_FILENO) == -1)
			free_all(c, "19840", "dup2 pipe 1");
		if (close(c->fd2[0]) == -1)
			free_all(c, "19840", "close pipe 1");
	}
	if (i > 0 && i % 2 == 1 && c->type[i - 1] == '|')
	{
		if (close(c->fd1[1]) == -1)
			free_all(c, "19840", "close unused pipe 2");
		if (dup2(c->fd1[0], STDIN_FILENO) == -1)
			free_all(c, "19840", "dup2 pipe 2");
		if (close(c->fd1[0]) == -1)
			free_all(c, "19840", "close pipe 2");
	}
	handle_pipe2(c, i);
}

static void	close_wait(int i, t_cmd *c, pid_t pid)
{
	if (i > 0 && c->type[i - 1] == '|' && i % 2 == 0)
	{
		if (close(c->fd2[0]) == -1)
			free_all(c, "", "close pipe 21");
		if (close(c->fd2[1]) == -1)
			free_all(c, "", "close pipe 22");
	}
	else if (i > 0 && c->type[i - 1] == '|' && i % 2 == 1)
	{
		if (close(c->fd1[0]) == -1)
			free_all(c, "", "close pipe 11");
		if (close(c->fd1[1]) == -1)
			free_all(c, "", "close pipe 12");
	}
	if (waitpid(pid, &g_exit_status, 0) < 0)
		free_all(c, "", strerror(errno));
	ft_check_exit_status(g_exit_status);
}

static void	run_in_child(t_cmd *c, int i)
{
	char	**ex;

	handle_pipe(c, i);
	ex = redirects_cut_off(c->cmd[i], c);
	if (!ex)
	{
		unlink("clucoheredoc");
		perror("redirect");
		exit (1);
	}
	if (i == 0 || c->type[i - 1] == '|'
		|| (c->type[i - 1] == 'r' && g_exit_status != 0)
		|| (c->type[i - 1] == '&' && g_exit_status == 0))
	{
		if (ft_isbuiltin(ex) == 0)
			run_execve(c, ex);
		else
			ft_run_builtin(ex, c);
	}
	i = 0;
	while (ex[i] != NULL)
		free(ex[i++]);
	free(ex);
	unlink("clucoheredoc");
	exit (0);
}

void	run_cmd(t_cmd *c, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		free_all(c, "19840", "fork");
	else if (pid == 0)
		run_in_child(c, i);
	else
		close_wait(i, c, pid);
}
