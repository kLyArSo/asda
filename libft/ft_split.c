/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:12:35 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/30 13:50:39 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (*s != '\0')
	{
		if (x == 0 && *s != c)
		{
			x = 1;
			count++;
		}
		if (x == 1 && *s == c)
			x = 0;
		s++;
	}
	return (count);
}

static int	len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	*ft_free(char ***temp, int i)
{
	char	**out;

	out = *temp;
	while (i >= 0)
	{
		free(out[i]);
		i--;
	}
	free(out);
	out = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**temp;
	int		i;
	int		cnt;

	if (!s)
		return (NULL);
	i = 0;
	cnt = count(s, c);
	temp = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	while (cnt--)
	{
		while (*s != '\0' && *s == c)
			s++;
		temp[i] = m_substr(s, 0, len(s, c));
		if (!temp[i])
			return (ft_free(&temp, i));
		s = s + len(s, c);
		i++;
	}
	temp[i] = 0;
	return (temp);
}
