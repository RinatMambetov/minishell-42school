/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 00:08:35 by cluco            #+#    #+#             */
/*   Updated: 2022/04/07 21:30:27 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void get_ret(char *s, char *ret, int i[2])
{
	if (s[i[1]] == 34 && ft_strchr(&s[i[1]], 34) != NULL)
	{
		while (s[++i[1]] != 34)
			ret[++i[0]] = s[i[1]];
		i[1]++;
		return;
	}
	if (s[i[1]] == 39 && ft_strchr(&s[i[1]], 39) != NULL)
	{
		while (s[++i[1]] != 39)
			ret[++i[0]] = s[i[1]];
		i[1]++;
		return;
	}
	if (s[i[1]] != ' ' && s[i[1]] != '>' && s[i[1]] != '<')
		ret[++i[0]] = s[i[1]++];
}

char *get_arg(char *s, int *k)
{
	int i[2];
	char *ret;

	i[1] = *k;
	i[0] = rotate_quotes_and_text(s, i[1]);
	ret = xmalloc(sizeof(char) * (i[0] - i[1] + 1));
	i[0] = -1;
	while (s[i[1]] != ' ' && s[i[1]] != '<' && s[i[1]] != '>' && (s[i[1]]))
		get_ret(s, ret, i);
	while (s[i[1]] == ' ')
		i[1]++;
	ret[++i[0]] = 0;
	*k = i[1];
	return (ret);
}
