/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:04:54 by ayghazal          #+#    #+#             */
/*   Updated: 2019/10/25 01:17:05 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		size(int nb)
{
	int count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		count = 1;
	}
	while (nb)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	unsigned int		nb;
	int					len;
	char				*res;

	len = size(n);
	if (!(res = (char *)malloc(len + 1)))
		return (NULL);
	res[len] = '\0';
	if (n < 0 && (nb = -n) != 0)
		res[0] = '-';
	else if (n == 0)
	{
		res[0] = 48;
		return (res);
	}
	else
		nb = n;
	len = len - 1;
	while (nb)
	{
		res[len--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (res);
}
