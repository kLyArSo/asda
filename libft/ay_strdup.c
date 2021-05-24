/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ay_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:20:23 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/21 12:25:32 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ay_strdup(const char *s1)
{
	char		*ptr;
	int			len;

	len = m_strlen(s1);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	ptr[len] = '\0';
	return (ptr);
}
