/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:08:22 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/02 17:40:38 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_node *node)
{
	while (node != NULL)
	{
		ft_putendl_fd(node->data, 1);
		node = node->next;
	}
}

t_node	*get_envp(char **env)
{
	int		i;
	t_node	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		push_node(&head, env[i]);
		i++;
	}
	return (head);
}

char	*ft_equal(char	*s1)
{
	char	*temp;
	char	*res;
	int		ls1;

	ls1 = 0;
	if (!s1)
		return (NULL);
	while (s1[ls1++])
		;
	temp = (char *)malloc((ls1 + 3));
	if (temp == NULL)
		return (NULL);
	res = temp;
	while (*s1 != '=')
		*temp++ = *s1++;
	*temp++ = '=';
	*temp++ = 39;
	*temp++ = '=';
	*temp++ = 39;
	*temp = '\0';
	return (res);
}

int	check_value(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			if (s[i + 1])
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_cases(char *s, int ret)
{
	int	i;

	if (ret == 0)
		ft_putendl_fd(s, 1);
	if (ret == 1)
	{
		ft_putstr_fd(s, 1);
		ft_putendl_fd("\"\"", 1);
	}
	if (ret == 2)
	{
		i = 0;
		while (s[i] != '=')
			ft_putchar_fd(s[i++], 1);
		i++;
		ft_putstr_fd("=\"", 1);
		while (s[i])
			ft_putchar_fd(s[i++], 1);
		ft_putendl_fd("\"", 1);
	}
}
