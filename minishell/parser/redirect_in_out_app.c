/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_out_app.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:17:41 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 12:39:48 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	input(char *s, int *j, t_cmd *c)
{
	int		fd;
	int		k;

	fd = 0;
	k = *j;
	if (s[k + 1] == ' ')
	{
		while (s[++k] == ' ')
			;
		check_extra_arrows(c, s[k]);
		fd = ft_get_fd(s, &k);
	}
	else if (s[k + 1] != '>')
		fd = ft_get_fd(s, &k);
	*j = k;
	if (fd >= 0 && dup2(fd, 0) < 0)
		free_all(c, "19840", strerror(errno));
	else
		return (-1);
	return (0);
}

void	durakskii_redirect(char *s, int *j, t_cmd *c)
{
	int		k;
	char	*tmp;
	int		fd;

	k = *j + 2;
	while (s[k] == ' ')
		k++;
	check_extra_arrows(c, s[k]);
	tmp = get_arg(s, &k);
	fd = open(tmp, O_TRUNC | O_CREAT | O_RDWR, 0664);
	close(fd);
	free (tmp);
	*j = k;
}

static int	append(char *s, int *j, t_cmd *c, int *oldfd)
{
	int		k;
	int		fd;
	char	*tmp;

	fd = -1000;
	k = *j;
	if (s[++k] == '<')
		check_extra_arrows(c, s[k + 1]);
	else if (s[k] == 0)
		free_all(c, "19840", "zsh: parse error near '\\n'");
	else if (s[k] == '>')
	{
		while (s[++k] == ' ')
			;
		check_extra_arrows(c, s[k]);
		tmp = get_arg(s, &k);
		fd = open(tmp, O_CREAT | O_RDWR | O_APPEND, 0664);
		free (tmp);
	}
	*oldfd = check_digit(s, *j);
	*j = k;
	return (fd);
}

int	output(char *s, int *j, t_cmd *c)
{
	int		k;
	int		fd;
	char	*tmp;
	int		oldfd;

	k = *j;
	oldfd = 1;
	fd = append(s, &k, c, &oldfd);
	if (fd == -1000)
	{
		while (s[k] == ' ')
			k++;
		check_extra_arrows(c, s[k]);
		tmp = get_arg(s, &k);
		fd = open(tmp, O_TRUNC | O_CREAT | O_RDWR, 0664);
		free (tmp);
		oldfd = check_digit(s, *j);
	}
	*j = k;
	if (fd == -1)
		return (fd);
	if (dup2(fd, oldfd) < 0)
		free_all(c, "19840", strerror(errno));
	return (fd);
}
