/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 12:23:41 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/22 15:54:33 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_pwd()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return(1);
    else
        ft_putendl_fd(cwd, 1);
    return (0);
}
