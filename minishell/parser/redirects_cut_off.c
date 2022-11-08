/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_cut_off.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:37:08 by cluco            #+#    #+#             */
/*   Updated: 2022/04/14 12:41:32 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int rotate_quotes_and_text(char *s, int i)
{
	int j;

	j = 0;
	while (s[i] != '<' && s[i] != '>' && s[i] != ' ' && (s[i]))
	{
		while (s[i] == 34 || s[i] == 39)
		{
			if (s[i] == 34 && ft_strchr(&s[i], 34) != NULL)
				while (s[++i] != 34)
					;
			if (s[i] == 39 && ft_strchr(&s[i], 39) != NULL)
				while (s[++i] != 39)
					;
			i++;
			j++;
		}
		if (j == 0)
			i++;
		j = 0;
	}
	return (i);
}

static int count_args(char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '>' || s[i] == '<')
		{
			while (s[i] == '<' || s[i] == '>')
				i++;
			while (s[i] == ' ')
				i++;
			i = rotate_quotes_and_text(s, i);
		}
		else
		{
			i = rotate_quotes_and_text(s, i);
			j++;
		}
	}
	return (j);
}

static int redirect_create(char *s, int *j, t_cmd *c)
{
	int k;

	k = *j;
	if (s[k] == '<')
	{
		if (s[k + 1] == '<')
		{
			ft_run_signals(3, c);
			heredoc(s, &k, c);
		}
		else if (s[k + 1] == '>')
			durakskii_redirect(s, &k, c);
		else if (input(s, &k, c) == -1)
			return (-1);
	}
	if (s[k] == '>')
		if (output(s, &k, c) == -1)
			return (-1);
	*j = k;
	return (0);
}

char **redirects_cut_off(char *s, t_cmd *c)
{
	char **ret;
	int j;
	int k;

	ret = xmalloc(sizeof(char *) * (count_args(s) + 1));
	k = 0;
	j = -1;
	while (s[k])
	{
		if (s[k] == '>' || s[k] == '<')
		{
			if (redirect_create(s, &k, c) == -1)
				return (NULL);
		}
		else
		{
			ret[++j] = get_arg(s, &k);
			if (ft_strlen(ret[j]) == 1 && s[k] == '>' && (ret[j][0] == '1' || ret[j][0] == '0' || ret[j][0] == '2'))
				free(ret[j--]);
		}
	}
	ret[++j] = NULL;
	return (ret);
}
