/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:18:15 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 12:25:36 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_ctrl(int sig)
{
	if (sig == 2)
		printf("\n");
	if (sig == 3)
		printf("Quit: %d\n", sig);
}

void
	ft_ctrl_d(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void
	ft_new_prompt(int sig)
{
	(void)sig;
	g_exit_status = EXIT_FAILURE;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void
	ft_sig_error(t_cmd *c)
{
	if (c)
		free_all(c, "178940", "Error signal");
	else
		ft_putendl_fd("Error signal", 2);
	exit(EXIT_FAILURE);
}

void
	ft_run_signals(int sig, t_cmd *c)
{
	if (sig == 1)
	{
		if (signal(SIGINT, ft_new_prompt) == SIG_ERR)
			ft_sig_error(c);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_sig_error(c);
	}
	if (sig == 2)
	{
		if (signal(SIGINT, ft_ctrl) == SIG_ERR)
			ft_sig_error(c);
		if (signal(SIGQUIT, ft_ctrl) == SIG_ERR)
			ft_sig_error(c);
	}
	if (sig == 3)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			ft_sig_error(c);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_sig_error(c);
	}
}
