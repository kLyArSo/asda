/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:20:49 by ayghazal          #+#    #+#             */
/*   Updated: 2019/10/22 21:45:57 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *temp1;
	char *temp2;

	temp1 = (char *)src;
	temp2 = (char *)dst;
	if (dst == src)
		return (dst);
	while (n--)
	{
		*temp2++ = *temp1++;
	}
	return (dst);
}
