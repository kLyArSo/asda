/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:06:41 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/03 12:04:09 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_id(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

int	export_error(char *s, int i)
{
	if (i == 0)
		fd_putstr("minishell: export: `", s,
			"': not a valid identifier\n", NULL);
	else if (i == 1)
		fd_putstr("minishell: unset: `", s,
			"': not a valid identifier\n", NULL);
	return (1);
}

int	get_arglen(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = arglen(s1);
	len2 = arglen(s2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

void	deletenode(t_node **head, char *pos)
{
	t_node	*tmp;
	t_node	*next;

	if (*head == NULL)
		return ;
	tmp = *head;
	if (ft_strncmp(tmp->data, pos, get_arglen(tmp->data, pos)) == 0)
	{
		*head = tmp->next;
		free(tmp->data);
		free(tmp);
		return ;
	}
	while (ft_strncmp(tmp->next->data, pos,
			get_arglen(tmp->next->data, pos)) && tmp != NULL)
		tmp = tmp->next;
	if (tmp == NULL || tmp->next == NULL)
		return ;
	next = tmp->next->next;
	free(tmp->next->data);
	free(tmp->next);
	tmp->next = next;
}

void	fd_putstr(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 != NULL)
		write(2, s1, ft_strlen(s1));
	if (s2 != NULL)
		write(2, s2, ft_strlen(s2));
	if (s3 != NULL)
		write(2, s3, ft_strlen(s3));
	if (s4 != NULL)
		write(2, s4, ft_strlen(s4));
}
