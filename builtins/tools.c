/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayghazal <ayghazal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:32:51 by ayghazal          #+#    #+#             */
/*   Updated: 2021/05/23 19:55:20 by ayghazal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int			ft_isabsolute(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return(1);
		i++;
	}
	return(0);
}

int			ft_ispath(char *s)
{
	return(s[0] == 'P' && s[1] == 'A' && s[2] == 'T' && s[3] == 'H');
}

void	print2d(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}

char	*ft_join(char const *s1, char const *s2)
{
	char		*temp;
	char		*res;
	int			ls1;
	int			ls2;

	ls1 = 0;
	ls2 = 0;
	if (!s1)
		return (NULL);
	while (s1[ls1++])
		;
	while (s2[ls2++])
		;
	temp = (char *)malloc((ls1 + 1) + ls2 - 1);
	if (temp == NULL)
		return (NULL);
	res = temp;
	while (*s1 != '\0')
		*temp++ = *s1++;
	*temp++ = '/';
	while (*s2 != '\0')
		*temp++ = *s2++;
	*temp = '\0';
	return (res);
}


void    push_node(t_node **head, char *newdata)
{
    t_node *newnode = malloc(sizeof(t_node));

    newnode->data = ay_strdup(newdata);
    newnode->next = *head;
    *head=newnode;

}

void    print_list(t_node *node)
{
    while (node != NULL)
    {
        ft_putendl_fd(node->data, 1);
        node = node->next;
    }
}

t_node     *get_envp(char **env)
{
    int i;
    t_node *head;

    i = 0;
    head = NULL;
    while(env[i])
    {
        push_node(&head, env[i]);
        i++;
    }
    return(head);

}

char	*ft_equal(char	*s1)
{
	char		*temp;
	char		*res;
	int			ls1;


	ls1 = 0;
	if (!s1)
		return (NULL);
	while (s1[ls1++])
		;
	temp = (char *)malloc((ls1 + 3));
	if (temp == NULL)
		return (NULL);
	res = temp;
	while (*s1 != '=')
		*temp++ = *s1++;
	*temp++ = '=';
	*temp++ = 39;
	*temp++ = '=';
	*temp++ = 39;
	*temp = '\0';
	return (res);
}

int     check_value(char *s)
{
    int i;

    i = 0;
    while(s[i])
    {
        if (s[i] == '=')
        {
            if(s[i+1])
                return(2);
            return(1);
        }
        i++;
    }
    return(0);
}

void    print_cases(char *s, int ret)
{
    int i;

    if (ret == 0)
        ft_putendl_fd(s, 1);
    if (ret == 1)
    {
        ft_putstr_fd(s, 1);
        ft_putendl_fd("\"\"", 1);
    }
    if (ret == 2)
    {
        i = 0;
        while(s[i] != '=')
            ft_putchar_fd(s[i++], 1);
        i++;
        ft_putstr_fd("=\"", 1);
        while(s[i])
            ft_putchar_fd(s[i++], 1);
        ft_putendl_fd("\"", 1);
    }
}



  
void swap(t_node *a, t_node *b)
{
    char *temp = a->data;
    a->data = b->data;
    b->data = temp;
}

t_node  *sort_list(t_node *start)
{
    int swapped; 
    int     i;
    t_node *ptr1;
    t_node *lptr = NULL;
  
    if (start == NULL)
        return NULL;
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
    return(start);
}

t_node *copyList(t_node* head)
{
    if (head == NULL) {
        return NULL;
    }
    else {
  
        t_node* newnode = (t_node*)malloc(sizeof(t_node));
  
        newnode->data = ay_strdup(head->data);
  
        newnode->next = copyList(head->next);
  
        return newnode;
    }
}

void deletelist(t_node **head_ref)
{
   t_node *current = *head_ref;
   t_node *next;
 
   while (current != NULL)
   {
       next = current->next;
       free(current->data);
       free(current);
       current = next;
   }
   *head_ref = NULL;
}


 void    print_export(t_node *node)
{
    int ret = 0;

    t_node *tmp;
    t_node *head_ref;

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

int     valid_id(char *s)
{
    int i;

    i = 0;
    if(!ft_isalpha(s[i]) && s[i] != '_')
        return(0);
    while(s[i] && s[i]!= '=')
    {
        if(ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
            i++;
        else    
            return(0);
    }
    return(1);
}

int    export_error(char *s, int i)
{
    if (i == 0)
        fd_putstr(2, "minishell: export: `", s, "': not a valid identifier\n", NULL);
    else if (i == 1)
        fd_putstr(2, "minishell: unset: `", s, "': not a valid identifier\n", NULL);
    return(1);
}


int     get_arglen(char *s1, char *s2)
{
    int len1 = arglen(s1);
    int len2 = arglen(s2);

    if (len1 > len2)
        return(len1);
    else
        return(len2);
}














void    deletenode(t_node **head, char *pos)
{
    int i = 0;
    t_node *tmp;
    t_node *next;
    
    if(*head == NULL)
        return;
    tmp = *head;
    
    // If head needs to be removed
    if(ft_strncmp(tmp->data, pos, get_arglen(tmp->data, pos)) == 0)
    {
        *head = tmp->next;
        free(tmp->data);
        free(tmp);
        return;
    }
    

    //Find Previous node of the node to be deleted 
    while (ft_strncmp(tmp->next->data, pos, get_arglen(tmp->next->data, pos)) && tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }

    //If position is more than number of nodes
    if (tmp == NULL || tmp->next == NULL)
        return;
    
    // Node tmp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    
    next = tmp->next->next;
    
    // Unlink the node from linked list
    free(tmp->next->data);
    free(tmp->next); // fre memory
    tmp->next = next;

}

void    fd_putstr(int fd, char    *s1, char   *s2, char   *s3, char   *s4)
{
    if (s1 != NULL)
        write(fd, s1, ft_strlen(s1));
    if (s2 != NULL)
        write(fd, s2, ft_strlen(s2));
    if (s3 != NULL)
        write(fd, s3, ft_strlen(s3));
    if (s4 != NULL)
        write(fd, s4, ft_strlen(s4));
}



















int     isequal(char *s)
{
    int i;

    i = 0;
    while(s[i])
    {
        if (s[i] == '=')
            return (1);
        i++;
    }
    return(0);
}

int     ft_listlen(t_arguments *node)
{
    int i;

    i = 0;
    while (node != NULL)
    {
        i++;
        node = node->next;
    }
    return(i);
}

char       **convertlist(t_arguments *node, char *s)
{
    char **str;
    int i;
    int len;

    i = 0;
    len = ft_listlen(node);
    str = (char **)malloc((len + 2) * sizeof(char*));
    str[i] = ay_strdup(s);
    i++;
    while(node != NULL)
    {
        str[i] = ay_strdup(node->arg);
        node = node->next;
        i++;
    }
    str[i] = NULL;
    return(str);
}

int     ft_envlen(t_node *node)
{
    int i;

    i = 0;
    while (node != NULL)
    {
        i++;
        node = node->next;
    }
    return(i);
}

char    **convertenv(t_node *node)
{
    char    **str;
    int i;
    int len;

    i = 0;
    len = ft_envlen(node);
    str = (char **)malloc((len + 1) * sizeof(char *));
    while (node != NULL)
    {
        str[i] = ay_strdup(node->data);
        node = node->next;
        i++;
    }
    str[i] = NULL;
    return(str);
}
