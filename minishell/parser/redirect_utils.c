/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:37:50 by greita            #+#    #+#             */
/*   Updated: 2022/04/14 12:39:00 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_get_fd(char *s, int *k)
{
	int		fd;
	char	*tmp;

	tmp = get_arg(s, k);
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return (fd);
}

int	check_digit(char *s, int i)
{
	if (s[i - 1] == '0' && s[i - 2] == ' ')
		return (0);
	if (s[i - 1] == '2' && s[i - 2] == ' ')
		return (2);
	return (1);
}
