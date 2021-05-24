/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:17:09 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/16 13:33:43 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    print_env(t_node *node)
{
    while (node != NULL)
    {
        if (isequal(node->data))
            ft_putendl_fd(node->data, 1);
        node = node->next;
    }
}


int     ft_env(t_arguments *arguments,t_node *head)
{

    if (arguments)
    {
        ft_putendl_fd("Too many argument", 2);
        return(1);
    }
    print_env(head);
    return(0);
}
