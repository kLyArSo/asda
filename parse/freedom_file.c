#include "functions_headerfile.h"

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
    tmp = ptr;
    while(ptr != NULL)      //free all sub nodes and contents
    {
        if (ptr->pipes == NULL)
            no_pipes_free(ptr);
        else if (ptr->pipes != NULL)
            yes_pipes_free(ptr);
        ptr = ptr->next;
    }
    ptr = tmp;
    tmp = ptr->next;
    ptr->next = NULL;
    ptr = tmp;
    while(ptr != NULL)//free all nodes except for the first one
    {
        tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}