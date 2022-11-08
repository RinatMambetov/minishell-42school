/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:58:56 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 11:51:08 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	ft_minlen(char *str1, char *str2)
{
	if (ft_strlen(str1) < ft_strlen(str2))
		return (ft_strlen(str1));
	else
		return (ft_strlen(str2));
}

void
	ft_strswap(char **str1, char **str2)
{
	char	*temp;
	char	*temp_str1;
	char	*temp_str2;

	temp_str1 = *str1;
	temp_str2 = *str2;
	temp = ft_strdup(*str1);
	*str1 = ft_strdup(*str2);
	*str2 = ft_strdup(temp);
	free(temp);
	free(temp_str1);
	free(temp_str2);
}

void
	ft_sort_env(char **env, t_cmd *c)
{
	int	i;
	int	j;
	int	arr_len;
	int	str_len;

	i = 0;
	arr_len = ft_arrlen(env);
	while (i < arr_len - 1)
	{
		j = 0;
		while (j < arr_len - 1 - i)
		{
			str_len = ft_minlen(env[j], env[j + 1]);
			if (ft_strncmp(env[j], env[j + 1], str_len) > 0)
				ft_strswap(&env[j], &env[j + 1]);
			if (!env[j] || !env[j + 1])
				free_all(c, "178940", "Error export");
			j++;
		}
		i++;
	}
}

char *
	ft_strjoin2(char *name, char *value)
{
	char	*str;
	char	*temp;

	str = ft_strjoin(name, "=");
	temp = str;
	str = ft_strjoin(str, value);
	free(temp);
	return (str);
}

char **
	ft_strdup2_add(char **arr, char *elem)
{
	int		len;
	int		i;
	char	**myarr;

	i = 0;
	len = ft_arrlen(arr);
	myarr = malloc(sizeof(char *) * (len + 2));
	if (!myarr)
		return (NULL);
	while (i < len)
	{
		myarr[i] = ft_strdup(arr[i]);
		i++;
	}
	myarr[i] = ft_strdup(elem);
	myarr[i + 1] = NULL;
	return (myarr);
}
