/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cluco <cluco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:03:06 by cluco             #+#    #+#             */
/*   Updated: 2022/04/18 10:02:10 by cluco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *check_in_env(char *s, char **env)
{
	int i;
	int j;
	char *tmp;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(s, env[i], ft_strlen(s)) == 0 && env[i][ft_strlen(s)] == '=')
		{
			j = ft_strlen(s) + 1;
			free(s);
			return (ft_substr(env[i], j,
							  ft_strlen(ft_strchr(env[i], '=') - 1)));
		}
	}
	free(s);
	tmp = malloc(1);
	tmp[0] = 0;
	return (tmp);
}

char *simple_text(char *s, int *j)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '$' && !(s[i] == 39 && ft_strchr(&s[i], 39) != NULL) && !(s[i] == 34 && ft_strchr(&s[i], 34) != NULL))
		i++;
	*j = *j + i;
	return (ft_substr(s, 0, i));
}

char *dollar(char *s, int *j, char **env)
{
	size_t i;

	if (s[1] == '?')
	{
		*j = *j + 2;
		return (ft_itoa(g_exit_status));
	}
	i = 1;
	while (s[i] && s[i] != ' ' && s[i] != 39 && s[i] != 34 && s[i] != '$')
		i++;
	*j = *j + i;
	return (check_in_env(ft_substr(s, 1, i - 1), env));
}

char *replace_var(char *s, char **env)
{
	int i;
	char *nl;
	char *tmp;
	char *tmp2;

	if (ft_strchr(s, '$') == NULL)
		return (ft_strdup(s));
	nl = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			tmp = dollar(&s[i], &i, env);
		else if (s[i] == 39 && ft_strchr(&s[i], 39) != NULL)
			tmp = durakskaya_kavichka(&s[i], &i);
		else if (s[i] == 34 && ft_strchr(&s[i], 34) != NULL)
			tmp = dvoynaia_kavichka(&s[i], &i, env);
		else
			tmp = simple_text(&s[i], &i);
		tmp2 = nl;
		nl = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	return (nl);
}
