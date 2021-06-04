/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylhouari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:49:22 by ylhouari          #+#    #+#             */
/*   Updated: 2021/06/04 15:49:24 by ylhouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	sig = 0;
	if (g_global.forked == 1)
	{
		g_global.ret = 1;
		put_strings("\nminishell~$ ", NULL, NULL, NULL);
		free(g_global.box->str);
		g_global.box->str = NULL;
		g_global.box->str = my_calloc(1);
	}
	else if (g_global.forked == 0)
	{
		g_global.ret = 130;
		ft_putchar_fd('\n', 1);
	}
}

void	handler2(int sig)
{
	sig = 0;
	if (g_global.forked == 0)
	{
		g_global.ret = 131;
		ft_putendl_fd("Quit: 3", 2);
		g_global.forked = 1;
	}
}

void	init_pwd(t_node **head)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	if (check_overwrite(*head, "PWD"))
		deletenode(head, "PWD");
	push_node(head, tmp);
	if (check_overwrite(*head, "OLDPWD"))
		deletenode(head, "OLDPWD");
	push_node(head, "OLDPWD");
	free(cwd);
	free(tmp);
}

t_node	*init_shell(char **env, int ac, char **av)
{
	t_node	*head;

	ac = 0;
	av = NULL;
	head = get_envp(env);
	shlvl(&head);
	init_pwd(&head);
	g_global.forked = 1;
	g_global.ret = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler2);
	return (head);
}
