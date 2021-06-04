/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:23:35 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/03 14:20:44 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_error(char *s)
{
	fd_putstr("minishell: ", s, ": ", "No such file or directory\n");
	return (1);
}

void	ft_close(t_redirections *redirections, int in, int out)
{
	if (redirections->next && out
		&& ft_strcmp(redirections->next->redirection_type, "<"))
		close(out);
	if (redirections->next && in
		&& !(ft_strcmp(redirections->next->redirection_type, "<")))
		close(in);
}

int	oflag(int i)
{
	if (i == 0)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	else
		return (O_CREAT | O_WRONLY | O_APPEND);
}

int	check_redirection(t_redirections *redirections)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	while (redirections != NULL)
	{
		if (!(ft_strcmp(redirections->redirection_type, "<")))
			in = open(redirections->redirection_file, O_RDONLY, S_IRWXU);
		if (!(ft_strcmp(redirections->redirection_type, ">")))
			out = open(redirections->redirection_file, oflag(0), 0644);
		if (!(ft_strcmp(redirections->redirection_type, ">>")))
			out = open(redirections->redirection_file, oflag(1), 0644);
		if ((in < 0 || out < 0))
			return (red_error(redirections->redirection_file));
		ft_close(redirections, in, out);
		redirections = redirections->next;
	}
	if (out)
		dup2(out, STDOUT_FILENO);
	if (in)
		dup2(in, STDIN_FILENO);
	return (0);
}
