/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ay_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:38:40 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/21 12:25:38 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ay_strjoin(char const *s1, char const *s2)
{
	char		*temp;
	char		*res;
	int			ls1;
	int			ls2;

	ls1 = 0;
	ls2 = 0;
	if (!s1)
		return (NULL);
	while (s1[ls1++])
		;
	while (s2[ls2++])
		;
	temp = (char *)malloc(ls1 + ls2 - 1);
	if (temp == NULL)
		return (NULL);
	res = temp;
	while (*s1 != '\0')
		*temp++ = *s1++;
	while (*s2 != '\0')
		*temp++ = *s2++;
	*temp = '\0';
	return (res);
}
