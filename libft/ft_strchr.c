/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:08:12 by ayghazal          #+#    #+#             */
/*   Updated: 2019/10/22 19:59:28 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)s;
	while (temp[i] != c)
	{
		if (temp[i] != '\0')
		{
			i++;
		}
		else
			return (NULL);
	}
	return (temp + i);
}
