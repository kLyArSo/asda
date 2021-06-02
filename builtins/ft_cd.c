/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 12:30:28 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/02 14:17:48 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error(char *s)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

char	*get_envar(t_node *node, char *s)
{
	int	len1;
	int	len2;

	len1 = 0;
	len2 = arglen(s);
	while (node != NULL)
	{
		len1 = arglen(node->data);
		if (len1 == len2)
		{
			if (ft_strncmp(node->data, s, len2) == 0)
				return (node->data + (len2 + 1));
		}
		node = node->next;
	}
	return (NULL);
}

void	update_pwd(t_node **head)
{
	char	*cwd;
	char	*tmp;
	int		i;

	i = check_overwrite(*head, "PWD");
	if (i == 1)
		tmp = ft_strjoin("OLDPWD=", (get_envar(*head, "PWD")));
	else
		tmp = ft_strdup("OLDPWD=");
	if (check_overwrite(*head, "OLDPWD"))
		deletenode(head, "OLDPWD");
	push_node(head, tmp);
	free(tmp);
	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	if (i == 1)
		deletenode(head, "PWD");
	push_node(head, tmp);
	free(cwd);
	free(tmp);
}

int	ft_cd(t_arguments *arguments, t_node **head)
{
	int		ret;
	char	*s;

	if (arguments == NULL)
	{
		s = get_envar(*head, "HOME");
		if (!s)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		s = arguments->arg;
	ret = chdir(s);
	if (ret < 0)
	{
		cd_error(arguments->arg);
		return (1);
	}
	update_pwd(head);
	return (0);
}
