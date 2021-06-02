#include "functions_headerfile.h"

void    init_post_free()
{
    g_global.box->formaptr->next = NULL;
    g_global.box->formaptr->line = NULL;
    g_global.box->formaptr->sliced_line = NULL;
    g_global.box->formaptr->pre_pipe_line = NULL;
    g_global.box->formaptr->command = NULL;
    g_global.box->formaptr->arguments = NULL;
    g_global.box->formaptr->redirections = NULL;
    g_global.box->formaptr->pipes = NULL;
    g_global.box->formaptr->pipe_presence = 0;
}

void    free_history()
{
    t_history   *ptr;
    t_history   *tmp;

    ptr = g_global.box->ptr;
    tmp = ptr;
    while(ptr != NULL)//free all contents
    {
        free(ptr->line);
        ptr->line = NULL;
        ptr = ptr->next;
    }
    ptr = tmp;
    while(ptr != NULL)//free all nodes
    {
        tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
    g_global.box->ptr = NULL;
}

void    free_tformat()
{
    t_format    *ptr;
    t_format    *tmp;

    ptr = g_global.box->formaptr;
    while(ptr != NULL)      //free all sub nodes and contents
    {
        if (ptr->pipes == NULL)
            no_pipes_free(ptr);
        else if (ptr->pipes != NULL)
        {
            free(ptr->line);
            ptr->line = NULL;
            yes_pipes_free(ptr);
        }
        ptr = ptr->next;
    }
    ptr = g_global.box->formaptr->next;
    while(ptr != NULL)//free all nodes except for the first one
    {
        tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}