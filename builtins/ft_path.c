/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:42:32 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/03 11:31:22 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_childpath(char *command, t_arguments *arguments, t_node *head)
{
	char	*path;
	char	**split;
	char	*cmd;

	if (ft_strcmp(command, "") == 0)
		cmd_error(command);
	if (ft_isabsolute(command))
		execve(command, convertlist(arguments, command), convertenv(head));
	path = getpath(head);
	if (!path)
		path_error(command);
	split = ft_split(path, ':');
	cmd = check_command(split, command);
	ft_free_split(split);
	if (cmd)
		execve(cmd, convertlist(arguments, command), convertenv (head));
	else
		cmd_error(command);
}

int	ft_path_forked(char *command, t_arguments *arguments, t_node *head)
{
	int		wstatus;
	int		pid;

	pid = fork();
	g_global.forked = 0;
	if (pid == 0)
	{
		ft_childpath(command, arguments, head);
		exit(0);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		g_global.forked = 1;
		if (WIFEXITED(wstatus))
			g_global.ret = WEXITSTATUS(wstatus);
	}
	return (g_global.ret);
}

int	ft_path_not_forked(char *command, t_arguments *arguments, t_node *head)
{
	char	*path;
	char	**split;
	char	*cmd;

	if (ft_strcmp(command, "") == 0)
		cmd_error(command);
	if (ft_isabsolute(command))
		execve(command, convertlist(arguments, command), convertenv(head));
	path = getpath(head);
	if (!path)
		path_error(command);
	split = ft_split(path, ':');
	cmd = check_command(split, command);
	ft_free_split(split);
	if (cmd)
		execve(cmd, convertlist(arguments, command), convertenv (head));
	else
		cmd_error(command);
	exit(0);
}

int	ft_path(char *command, t_arguments *arguments, t_node *head)
{	
	if (g_global.p == 0)
		ft_path_forked(command, arguments, head);
	else if (g_global.p == 5)
		ft_path_not_forked(command, arguments, head);
	return (0);
}
