/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:32:51 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/02 17:38:09 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_isabsolute(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_join(char const *s1, char const *s2)
{
	char	*temp;
	char	*res;
	int		ls1;
	int		ls2;

	ls1 = 0;
	ls2 = 0;
	if (!s1)
		return (NULL);
	while (s1[ls1++])
		;
	while (s2[ls2++])
		;
	temp = (char *)malloc((ls1 + 1) + ls2 - 1);
	if (temp == NULL)
		return (NULL);
	res = temp;
	while (*s1 != '\0')
		*temp++ = *s1++;
	*temp++ = '/';
	while (*s2 != '\0')
		*temp++ = *s2++;
	*temp = '\0';
	return (res);
}

void	push_node(t_node **head, char *newdata)
{
	t_node	*newnode;

	newnode = malloc(sizeof(t_node));
	newnode->data = ay_strdup(newdata);
	newnode->next = *head;
	*head = newnode;
}
