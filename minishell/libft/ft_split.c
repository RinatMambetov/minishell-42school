/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:51:37 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 12:51:38 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_countwds(char const *s, char c)
{
	size_t	i;
	size_t	nbr_word;
	size_t	word;

	i = 0;
	nbr_word = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			word = 0;
		if (s[i] != c && word == 0)
		{
			nbr_word++;
			word = 1;
		}
		i++;
	}
	return (nbr_word);
}

static	size_t	ft_lenword(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static	char	**ft_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
	return (NULL);
}

static	char	*ft_strndup(const char *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (n +1));
	if (!str)
		return (NULL);
	while (n > 0)
	{
		str[i] = s[i];
		i++;
		n--;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	next;
	size_t	count_words;
	char	**str;

	next = 0;
	if (!s)
		return (NULL);
	count_words = ft_countwds(s, c);
	str = (char **)malloc(sizeof (char *) * (count_words + 1));
	if (!str)
		return (NULL);
	while (next < count_words)
	{
		while (*s != '\0' && *s == c)
			s++;
		str[next] = ft_strndup(s, ft_lenword(s, c));
		if (!str[next])
			ft_free(str);
		s = s + ft_lenword(s, c);
		next++;
	}
	str[next] = NULL;
	return (str);
}
