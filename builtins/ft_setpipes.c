/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setpipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:02:30 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/03 19:14:09 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_len(t_pipes *pipes)
{
	t_pipes	*tmp;
	int		i;

	i = 0;
	tmp = pipes;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_duppipes(int i, int len, int fd[][2])
{
	int	prev;

	prev = i - 1;
	if (i == 0)
	{
		dup2(fd[i][1], 1);
		close(fd[i][0]);
		close(fd[i][1]);
	}
	if (i > 0 && (i < (len - 1)))
	{
		dup2(fd[prev][0], 0);
		close(fd[prev][0]);
		dup2(fd[i][1], 1);
		close(fd[i][1]);
		close(fd[i][0]);
	}
	if (i == (len - 1))
	{
		dup2(fd[prev][0], 0);
		close(fd[prev][0]);
	}
}

void	ft_closepipes(int i, int len, int fd[][2])
{
	if (i == 0)
		close(fd[i][1]);
	if (i > 0 && (i < (len - 1)))
	{
		close(fd[i - 1][0]);
		close(fd[i][1]);
	}
	if (i == (len - 1))
		close(fd[i - 1][0]);
}

void	ft_waitpipes(int len, int *pid)
{
	int	i;
	int	wstatus;

	i = -1;
	while (++i < len)
	{
		waitpid(pid[i], &wstatus, 0);
		g_global.forked = 1;
		if (WIFEXITED(wstatus))
			g_global.ret = WEXITSTATUS(wstatus);
	}
}

void	ft_setpipes(t_pipes *pipes, t_node **head)
{
	int	i;
	int	len;
	int	pid[250];
	int	fd[250][2];

	i = -1;
	len = pipe_len(pipes);
	while (++i < len)
	{
		if (i != len - 1)
			pipe(fd[i]);
		pid[i] = fork();
		g_global.forked = 0;
		if (pid[i] == 0)
		{
			ft_duppipes(i, len, fd);
			ft_exec_cmd(pipes->command, pipes->arguments,
				pipes->redirections, head);
			exit(0);
		}
		else
			ft_closepipes(i, len, fd);
		pipes = pipes->next;
	}
	ft_waitpipes(len, pid);
}
