/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:51:50 by ayghazal          #+#    #+#             */
/*   Updated: 2019/10/20 21:47:43 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = (char *)malloc(count * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, size * count);
	return (ptr);
}
