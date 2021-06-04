/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:09:06 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/03 18:04:56 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ispath(char *s)
{
	return (s[0] == 'P' && s[1] == 'A' && s[2] == 'T' && s[3] == 'H');
}

void	pwd_error(void)
{
	ft_putstr_fd("minishell: cd: error retrieving current directory", 2);
	ft_putstr_fd(": getcwd: cannot access parent directories", 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	set_lvl(char **s, t_node **head)
{
	int		lvl;
	char	*shlvl;

	lvl = 1;
	lvl += ft_atoi(s[1]);
	free(s[1]);
	s[1] = ft_itoa(lvl);
	shlvl = ft_strjoin("SHLVL=", s[1]);
	deletenode(head, "SHLVL");
	push_node(head, shlvl);
	free(shlvl);
	ft_free_split(s);
}

void	shlvl(t_node **head)
{
	char	**s;
	t_node	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		s = ft_split(tmp->data, '=');
		if (ft_strcmp(s[0], "SHLVL") == 0)
		{
			set_lvl(s, head);
			return ;
		}
		else
			ft_free_split(s);
		tmp = tmp->next;
		if (tmp == NULL)
			push_node(head, "SHLVL=1");
	}
}
