/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc_and_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:57:32 by cluco            #+#    #+#             */
/*   Updated: 2022/03/29 00:01:26 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_extra_arrows(t_cmd *c, char ch)
{
	if (ch == '<')
		free_all(c, "19840", "bash: parse error near '<'");
	else if (ch == '>')
		free_all(c, "19840", "bash: parse error near '>'");
}

static void dup_2(char *limiter, char *line, int fd, t_cmd *c)
{
	free(limiter);
	free(line);
	close(fd);
	fd = open("clucoheredoc", O_RDWR);
	if (dup2(fd, 0) < 0)
	{
		unlink("clucoheredoc");
		free_all(c, "19840", strerror(errno));
	}
	close(fd);
}

static void heredoc_dup2(char *limiter, t_cmd *c)
{
	char *line;
	int fd;

	fd = open("clucoheredoc", O_TRUNC | O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd < 0)
	{
		unlink("clucoheredoc");
		free(limiter);
		free_all(c, "19840", strerror(errno));
	}
	line = xmalloc(2);
	line[0] = 13;
	line[1] = 0;
	while (1)
	{
		free(line);
		line = readline("> ");
		rl_redisplay();
		if (ft_strcmp(limiter, line) == 0)
			break;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	dup_2(limiter, line, fd, c);
}

void heredoc(char *s, int *i, t_cmd *c)
{
	int k;
	char *limiter;

	k = *i + 2;
	while (s[k] == ' ')
		k++;
	check_extra_arrows(c, s[k]);
	limiter = get_arg(s, &k);
	heredoc_dup2(limiter, c);
	*i = k;
}
