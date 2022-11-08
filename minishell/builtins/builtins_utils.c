/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:06:33 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 11:51:54 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int
	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

char **
	ft_strdup2(char **arr)
{
	int		i;
	int		len;
	char	**myarr;

	i = 0;
	len = ft_arrlen(arr);
	myarr = malloc(sizeof(char *) * (len + 1));
	if (!myarr)
		return (NULL);
	while (i < len)
	{
		myarr[i] = ft_strdup(arr[i]);
		if (!myarr[i])
			return (NULL);
		i++;
	}
	myarr[i] = NULL;
	return (myarr);
}
