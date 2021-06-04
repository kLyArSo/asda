/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:07:30 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/02 17:37:36 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap(t_node *a, t_node *b)
{
	char	*temp;

	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

t_node	*sort_list(t_node *start)
{
	int		swapped;
	t_node	*ptr1;
	t_node	*lptr;

	lptr = NULL;
	if (start == NULL)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->data, ptr1->next->data) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	return (start);
}

t_node	*copyList(t_node *head)
{
	t_node	*newnode;

	if (head == NULL)
		return (NULL);
	else
	{
		newnode = (t_node *)malloc(sizeof(t_node));
		newnode->data = ay_strdup(head->data);
		newnode->next = copyList(head->next);
		return (newnode);
	}
}

void	deletelist(t_node **head_ref)
{
	t_node	*current;
	t_node	*next;

	current = *head_ref;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void	print_export(t_node *node)
{
	int		ret;
	t_node	*tmp;
	t_node	*head_ref;

	ret = 0;
	tmp = copyList(node);
	tmp = sort_list(tmp);
	head_ref = tmp;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ret = check_value(tmp->data);
		print_cases(tmp->data, ret);
		tmp = tmp->next;
	}
	deletelist(&head_ref);
}
