/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:28:54 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/23 09:10:51 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_unset(t_arguments *arguments, t_node **head)
{
    int ret;

    ret = 0;
    while(arguments != NULL)
    {
        if (valid_id(arguments->arg) && !isequal(arguments->arg))
        {
            if (check_overwrite(*head, arguments->arg) == 1)
                deletenode(head, arguments->arg);
        }
        else
            ret = export_error(arguments->arg, 1);
        arguments = arguments->next;
    }
    return(ret);
}
