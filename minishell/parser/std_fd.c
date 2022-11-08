/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:00:05 by cluco            #+#    #+#             */
/*   Updated: 2022/03/28 22:59:23 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int *save_std(t_cmd *c)
{
	int *fdstd;

	fdstd = xmalloc(sizeof(int) * 3);
	fdstd[0] = dup(0);
	fdstd[1] = dup(1);
	fdstd[2] = dup(2);
	if (fdstd[0] < 0 || fdstd[1] < 0 || fdstd[2] < 0)
		free_all(c, "40", "dup");
	return (fdstd);
}

void set_std_fd(t_cmd *c)
{
	if (dup2(c->std_fd[0], 0) < 0 || dup2(c->std_fd[1], 1) < 0 || dup2(c->std_fd[2], 2) < 0)
		free_all(c, "178940", "dup2");
}
