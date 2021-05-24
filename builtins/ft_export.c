/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:32:28 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/23 09:10:42 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     arglen(char *s)
{
    int i;
    i = 0;

    while(s[i] && s[i] != '=')
        i++;
    return(i);
}



int     check_overwrite(t_node *node, char *s)
{
    int len1;
    int len2;
    
    len1 = 0;
    len2 = arglen(s);
    while (node != NULL)
    {
        len1 = arglen(node->data);
        if (len1 == len2)
        {
            if  (ft_strncmp(node->data, s, len2) == 0)
                return(1);
        }
        node = node->next;
    }
    return(0); 
}

int     ft_export(t_arguments *arguments, t_node **head)
{
    int ret;

    ret = 0;
    if (arguments == NULL)
        print_export(*head);
    while (arguments != NULL)
    {
        if (valid_id(arguments->arg))
        {
            if (check_overwrite(*head, arguments->arg) == 1)
            {
                if(isequal(arguments->arg))
                {
                    deletenode(head, arguments->arg);
                    push_node(head, arguments->arg);
                }
            }
            else
                push_node(head, arguments->arg);
        }
        else
            ret = export_error(arguments->arg, 0);
        arguments = arguments->next;
    }
    return(ret);
}