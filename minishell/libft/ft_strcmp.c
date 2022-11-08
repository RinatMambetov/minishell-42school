/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:51:42 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 12:51:44 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	result;
	int	i;

	if ((s1 && !(s2)) || (!(s1) && s2))
		return (1);
	result = 0;
	i = -1;
	while (s1[++i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			continue ;
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (result);
	if (s1[i] > s2[i])
		return (1);
	return (-1);
}
