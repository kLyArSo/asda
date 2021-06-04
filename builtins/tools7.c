/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:54:08 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/03 12:04:33 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_error(char *s)
{
	fd_putstr("minishell: ", s, ": command not found\n", NULL);
	exit(127);
}

void	path_error(char *s)
{
	fd_putstr("minishell: ", s, ": No such file or directory\n", NULL);
	exit(1);
}

char	*getpath(t_node *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		if (ft_ispath(node->data))
			return (node->data + 5);
		node = node->next;
	}
	return (NULL);
}

char	*check_command(char **split, char *cmd)
{
	char	*command;
	int		i;

	i = 0;
	while (split[i])
	{
		command = ft_join(split[i], &cmd[0]);
		if (open(command, O_RDONLY) > 0)
			return (command);
		i++;
	}
	return (NULL);
}
