/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:46:02 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 12:46:03 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_res_check(unsigned int c, int sign)
{
	if (c > 2147483648 && sign == -1)
		return (0);
	if (c > INT_MAX && sign == 1)
		return (-1);
	return (c);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	res;
	size_t			i;

	sign = 1;
	res = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	res = ft_res_check(res, sign);
	return (res * sign);
}
