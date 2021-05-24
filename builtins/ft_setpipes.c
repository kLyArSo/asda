/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setpipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:02:30 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/23 10:16:36 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_len(t_pipes *pipes)
{
	t_pipes *tmp;
	int i;

	i = 0;
	tmp = pipes;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return(i);
}

int    ft_setpipes(t_pipes *pipes, t_node **head)
{
	int i = -1;
	int wstatus;
	int len;
	int prev;
	int pid[100];
	int fd[100][2];
	
	len = pipe_len(pipes);
	while (++i < len)
	{
		if (i != len-1)
			pipe(fd[i]);
		pid[i] = fork();
		g_global.forked = 0;
		if (pid[i] == 0)
		{
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
			ft_exec_cmd(pipes->command, pipes->arguments, pipes->redirections, head);
			exit(0);
		}
		else
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
		pipes = pipes->next;
	}
	i = -1;
	while(++i < len)
	{
		waitpid(pid[i], &wstatus, 0);
		g_global.forked = 1;
		if (WIFEXITED(wstatus))
            g_global.ret = WEXITSTATUS(wstatus);
	}
	return(g_global.ret);
}