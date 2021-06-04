/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:01:55 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/02 17:29:33 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isequal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_listlen(t_arguments *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

char	**convertlist(t_arguments *node, char *s)
{
	char	**str;
	int		i;
	int		len;

	i = 0;
	len = ft_listlen(node);
	str = (char **)malloc((len + 2) * sizeof(char *));
	str[i] = ay_strdup(s);
	i++;
	while (node != NULL)
	{
		str[i] = ay_strdup(node->arg);
		node = node->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

int	ft_envlen(t_node *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

char	**convertenv(t_node *node)
{
	char	**str;
	int		i;
	int		len;

	i = 0;
	len = ft_envlen(node);
	str = (char **)malloc((len + 1) * sizeof(char *));
	while (node != NULL)
	{
		str[i] = ay_strdup(node->data);
		node = node->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
