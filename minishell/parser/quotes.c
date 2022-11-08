/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:18:34 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 12:34:57 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*durakskaya_kavichka(char *s, int *j)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] && count < 2)
	{
		if (s[i] == 39)
			count++;
		i++;
	}
	*j = *j + i;
	return (ft_substr(s, 0, i));
}

static int	ft_check_quote(char **tmp, char sign, int *count)
{
	if (sign == 39)
	{
		*tmp = ft_strdup("\'");
		return (0);
	}
	if (sign == 34)
	{
		*tmp = ft_strdup("\"");
		*count += 1;
		return (0);
	}
	return (1);
}

char	*dvoynaia_kavichka(char *s, int *j, char **env)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*nl;
	int		count;

	i = 0;
	count = 0;
	nl = ft_strdup("");
	while (s[i] && count < 2)
	{
		if (s[i] == '$')
			tmp = dollar(&s[i], &i, env);
		else if (!ft_check_quote(&tmp, s[i], &count))
			i++;
		else
			tmp = simple_text(&s[i], &i);
		tmp2 = nl;
		nl = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	*j = *j + i;
	return (nl);
}
