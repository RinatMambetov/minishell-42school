/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:45:22 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 12:45:25 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(int num)
{
	int		i;

	i = 1;
	if (num < 0)
	{
		i++;
		num *= -1;
	}
	while (num > 9)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static	int	ft_division(int len)
{
	int		i;

	i = 1;
	if (len == 1)
		return (1);
	while (len > 1)
	{
		i *= 10;
		len--;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	int		lennum;
	char	*res;

	i = 0;
	len = ft_num_len(n);
	lennum = len;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
		i++;
		len--;
	}
	while (i < lennum)
		res[i++] = ((n / ft_division(len--)) % 10) + 48;
	res[i] = '\0';
	return (res);
}
