/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:51:00 by greita            #+#    #+#             */
/*   Updated: 2022/04/11 12:51:01 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*vrb;

	vrb = (unsigned char *)dest;
	while (len != 0)
	{
		*vrb = (unsigned char)c;
		vrb++;
		len--;
	}
	return (dest);
}
