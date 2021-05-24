/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 12:37:49 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/15 17:28:55 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_echon(char *s)
{
    int i = 0;

    if (s == NULL)
        return(0);
    if (s[i] != '-')
        return(0);
    i++;
    while(s[i])
    {
        if (s[i] != 'n')
            return(0);
        i++;
    }
    return(1);
}

int     ft_echo(t_arguments *arguments)
{
    int n = 0;

    if (arguments != NULL)
    {
        while(ft_echon(arguments->arg) == 1)
        {
            n = 1;
            arguments = arguments->next;
            if (arguments == NULL)
                break;
        }
    }
    while (arguments != NULL)
    {
        ft_putstr_fd(arguments->arg, 1);
        if (arguments->next != NULL)
            ft_putchar_fd(' ', 1);
        arguments = arguments->next;
    }
    if (n == 0)
        ft_putchar_fd('\n', 1);
    return(0);   
}
