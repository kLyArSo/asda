/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:42:32 by ayghazal          #+#    #+#             */
/*   Updated: 2021/06/02 14:01:09 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *getpath(t_node *node)
{
    int i;
    i = 0;
    while (node != NULL)
    {
        if (ft_ispath(node->data))
        {
            return(node->data + 5);
        }
        node = node->next;
    }
    return(NULL);
}

char     *check_command(char **split, char *cmd)
{
    char *command;
    int i = 0;

    while (split[i])
    {
        command = ft_join(split[i], &cmd[0]);
        if (open(command, O_RDONLY) > 0)
            return(command);
        i++;
    }
    return(NULL);
}

int    check_redirection(t_redirections *redirections, t_node *head)
{
    int in;
    int out;

    in = 0;
    out = 0;
    while(redirections != NULL)
    {
        if (!(ft_strcmp(redirections->redirection_type, "<")))
            in = open(redirections->redirection_file,  O_RDONLY, S_IRWXU);
        if(!(ft_strcmp(redirections->redirection_type, ">")))
            out = open(redirections->redirection_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if(!(ft_strcmp(redirections->redirection_type, ">>")))
            out = open(redirections->redirection_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if ((in < 0 || out < 0))
        {
            fd_putstr(2, "minishell: ", redirections->redirection_file, ": ", "No such file or directory\n");
            return(1);
        }
        if (redirections->next && out && ft_strcmp(redirections->next->redirection_type, "<"))
            close(out);
        if (redirections->next && in && !(ft_strcmp(redirections->next->redirection_type, "<")))
            close(in);
        redirections = redirections->next;
    }
    if(out)
        dup2(out, STDOUT_FILENO);
    if(in)
        dup2(in, STDIN_FILENO);
    return(0);
}

void    cmd_error(char *s)
{
    fd_putstr(2, "minishell: ", s, ": command not found\n", NULL);
    exit(127);
}

void    path_error(char *s)
{
    fd_putstr(2, "minishell: ", s, ": No such file or directory\n", NULL);
    exit(1);
}

int     ft_path_forked(char *command, t_arguments *arguments, t_node *head)
{
    int wstatus;
    char *path;
    char **split;
    char  *cmd;
    int pid;

    pid = fork();
    g_global.forked = 0;
    if (pid == 0)
    {
        if (ft_strcmp(command, "") == 0)
            cmd_error(command);
        if (ft_isabsolute(command))
            execve(command, convertlist(arguments, command), convertenv(head));
        if (!(path = getpath(head)))
        {
            path_error(command);
        }
        split = ft_split(path, ':');
        cmd = check_command(split, command);
        ft_free_split(split);
        if (cmd)
            execve(cmd, convertlist(arguments, command), convertenv (head));
        else
            cmd_error(command);
        exit(0);
    }
    else
    {
        waitpid(pid, &wstatus, 0);
        g_global.forked = 1;
        if (WIFEXITED(wstatus))
            g_global.ret = WEXITSTATUS(wstatus);
    }
    return(g_global.ret);
}

int     ft_path_not_forked(char *command, t_arguments *arguments, t_node *head)
{
    char *path;
    char **split;
    char  *cmd;
    
    if (ft_strcmp(command, "") == 0)
            cmd_error(command);
    if (ft_isabsolute(command))
        execve(command, convertlist(arguments, command), convertenv(head));
    if (!(path = getpath(head)))
    {
        path_error(command);
    }
    split = ft_split(path, ':');
    cmd = check_command(split, command);
    ft_free_split(split);
    if (cmd)
        execve(cmd, convertlist(arguments, command), convertenv (head));
    else
    {
        cmd_error(command);
    }
    exit(0);
}


int     ft_path(char *command, t_arguments *arguments, t_node *head)
{
    
    if (g_global.p == 0)
        ft_path_forked(command, arguments, head);
    else if (g_global.p == 5)
        ft_path_not_forked(command, arguments, head);
    return(0);
}
