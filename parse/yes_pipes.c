#include "functions_headerfile.h"

void    free_sliced_contents_yp(t_linedata *ptr)
{
    while   (ptr != NULL)
    {
        free(ptr->slice);
        ptr->slice = NULL;
        ptr = ptr->next;
    }
}

void    free_sliced_nodes_yp(t_pipes *ptr)
{
    t_linedata *tmp_1;
    t_linedata *tmp_2;

    tmp_1 = ptr->sliced_line;
    while(tmp_1 != NULL)
    {
        tmp_2 = tmp_1->next;
        free(tmp_1);
        tmp_1 = tmp_2;
    }
    ptr->sliced_line = NULL;
}

void    free_arg_nodes_yp(t_pipes *ptr)
{
    t_arguments *tmp_1;
    t_arguments *tmp_2;

    tmp_1 = ptr->arguments;
    while(tmp_1 != NULL)
    {
        tmp_2 = tmp_1->next;
        free(tmp_1);
        tmp_1 = tmp_2;
    }
    ptr->arguments = NULL;
}

void    free_red_nodes_yp(t_pipes *ptr)
{
    t_redirections *tmp_1;
    t_redirections *tmp_2;

    tmp_1 = ptr->redirections;
    while(tmp_1 != NULL)
    {
        tmp_2 = tmp_1->next;
        free(tmp_1);
        tmp_1 = tmp_2;
    }
    ptr->redirections = NULL;
}

void    yes_pipes_free(t_format  *tmp)
{
    t_pipes *ptr;

    ptr = tmp->pipes;
    while(ptr != NULL)
    {
        if (ptr->line != NULL)
        {
            free(ptr->line);
            ptr->line = NULL;
        }
        if (ptr->sliced_line != NULL)
            free_sliced_contents_yp(ptr->sliced_line);
        if (ptr->sliced_line != NULL)
            free_sliced_nodes_yp(ptr);
        if (ptr->arguments != NULL)
            free_arg_nodes_yp(ptr);
        if (ptr->redirections != NULL)
            free_red_nodes_yp(ptr);
        ptr = ptr->next;
    }
}