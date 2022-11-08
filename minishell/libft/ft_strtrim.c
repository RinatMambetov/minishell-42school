/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:52:10 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 12:52:12 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	bin;
	size_t	end;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	bin = 0;
	while (s1[bin] && ft_strchr(set, s1[bin]))
		bin++;
	end = ft_strlen(s1 + bin);
	if (end)
		while (s1[end + bin - 1] != 0 && ft_strchr(set, s1[end + bin - 1]) != 0)
			end--;
	new = malloc(sizeof(char) * end + 1);
	if (!new)
		return (NULL);
	ft_strncpy(new, s1 + bin, end);
	new[end] = '\0';
	return (new);
}
