/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:04:54 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/30 13:44:47 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(int nb)
{
	int	count;

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

char	*ft_itoa(int n)
{
	unsigned int		nb;
	int					len;
	char				*res;

	len = size(n);
	res = (char *)malloc(len + 1);
	if (!res)
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
