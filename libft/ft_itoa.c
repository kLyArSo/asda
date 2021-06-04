/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:04:54 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/03 16:43:14 by ayghazal         ###   ########.fr       */
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
	t_itvar	var;

	var.len = size(n);
	var.res = (char *)malloc(var.len + 1);
	var.res[var.len] = '\0';
	if (n < 0)
	{
		var.nb = -n;
		if (var.nb != 0)
			var.res[0] = '-';
	}
	else if (n == 0)
	{
		var.res[0] = 48;
		return (var.res);
	}
	else
		var.nb = n;
	var.len = var.len - 1;
	while (var.nb)
	{
		var.res[var.len--] = (var.nb % 10) + '0';
		var.nb = var.nb / 10;
	}
	return (var.res);
}
