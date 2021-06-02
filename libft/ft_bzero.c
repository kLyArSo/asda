/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:50:36 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/30 13:42:17 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *argv, size_t n)
{
	unsigned char	*temp;

	temp = argv;
	while (n--)
	{
		*temp = 0;
		temp++;
	}
}
