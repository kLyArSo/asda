#include "functions_headerfile.h"
/*
void    *dollar_exception_yes_pipes(char        **env, t_format    *rtp)
{
    t_var_rep       *data;
    t_arguments     *arg_ptr;
    char            *kass;
    t_pipes         *ptr;
    data = malloc(sizeof(t_var_rep));
    ptr = rtp->pipes;

    while (ptr != NULL)
    {
        arg_ptr = ptr->arguments;
        if (ptr->command != NULL && ptr->command[0] == '$' && ptr->command[1] != '\0')
        {
            data->variable_name = fetch_var_name(ptr->command, 1);
            data->variable_content = fetch_variable_content(env, data->variable_name);
            if (my_strcmp(data->variable_content, "") == 0)
            {
                while (arg_ptr != NULL)
                {
                    if (arg_ptr->arg[0] == '$')
                    {
                        data->variable_name = fetch_var_name(arg_ptr->arg, 1);
                        data->variable_content = fetch_variable_content(env, data->variable_name);
                        if (my_strcmp(data->variable_content, "") != 0)
                        {
                            kass = ptr->command;
                            ptr->command = arg_ptr->arg;
                            arg_ptr->arg = kass;
                            return (NULL);
                        }
                    }
                    else if (arg_ptr->arg[0] != '$')
                    {
                        kass = ptr->command;
                        ptr->command = arg_ptr->arg;
                        arg_ptr->arg = kass;
                        return (NULL);
                    }
                    arg_ptr = arg_ptr->next;
                }
            }
        }
        ptr = ptr->next;
    }
    return (NULL);
}

void    *dollar_exceptions_no_pipes(char        **env, t_format    *ptr)
{
    t_var_rep       *data;
    t_arguments     *arg_ptr;
    char            *kass;
    data = malloc(sizeof(t_var_rep));
    arg_ptr = ptr->arguments;

    if (ptr->command != NULL && ptr->command[0] == '$' && ptr->command[1] != '\0')
    {
        data->variable_name = fetch_var_name(ptr->command, 1);
        data->variable_content = fetch_variable_content(env, data->variable_name);
        if (my_strcmp(data->variable_content, "") == 0)
        {
            while (arg_ptr != NULL)
            {
                if (arg_ptr->arg[0] == '$')
                {
                    data->variable_name = fetch_var_name(arg_ptr->arg, 1);
                    data->variable_content = fetch_variable_content(env, data->variable_name);
                    if (my_strcmp(data->variable_content, "") != 0)
                    {
                        kass = ptr->command;
                        ptr->command = arg_ptr->arg;
                        arg_ptr->arg = kass;
                        return (NULL);
                    }
                }
                else if (arg_ptr->arg[0] != '$')
                {
                    kass = ptr->command;
                    ptr->command = arg_ptr->arg;
                    arg_ptr->arg = kass;
                    return (NULL);
                }
                arg_ptr = arg_ptr->next;
            }
        }
    }
    return (NULL);
}*/

void    cleanse_yes_pipes(char        **env, t_format    *ptr)
{
    t_pipes         *tmp_pipes;
    t_arguments     *tmp_args;
    t_redirections  *tmp_redirections;

    tmp_pipes = ptr->pipes;
    //dollar_exception_yes_pipes(env, ptr);
    while(tmp_pipes != NULL)
    {
        if (tmp_pipes->command != NULL)
        {
            tmp_pipes->command = dollar_treatment(env, tmp_pipes->command);
            //tmp_pipes->command = quote_slash(tmp_pipes->command);
        }
        tmp_args = tmp_pipes->arguments;
        while (tmp_args != NULL)
        {
            tmp_args->arg = dollar_treatment(env,  tmp_args->arg);
            //tmp_args->arg = quote_slash( tmp_args->arg);
            tmp_args = tmp_args->next;
        }
        tmp_redirections = tmp_pipes->redirections;
        while (tmp_redirections != NULL)
        {
            tmp_redirections->redirection_type = dollar_treatment(env, tmp_redirections->redirection_type);
            //tmp_redirections->redirection_type = quote_slash(tmp_redirections->redirection_type);
            tmp_redirections->redirection_file = dollar_treatment(env, tmp_redirections->redirection_file);
            //tmp_redirections->redirection_file = quote_slash(tmp_redirections->redirection_file);
            tmp_redirections = tmp_redirections->next;
        }
        tmp_pipes = tmp_pipes->next;
    }
}
int     dash_through_ws(char    *str)
{
    int i;

    i = 0;
    while(str[i] != 0 && is_white_space(str[i]) == 1)
        i++;
    return (i);
}
void    cleanse_no_pipes(char        **env, t_format    *ptr)
{
    t_arguments     *tmp_args;
    t_redirections  *tmp_redirections;

    //dollar_exceptions_no_pipes(env, ptr);
    if (ptr->command != NULL)
    {
        ptr->command = dollar_treatment(env, ptr->command);
        //ptr->command = quote_slash(ptr->command);
    }
    tmp_args = ptr->arguments;
    while (tmp_args != NULL)
    {
        tmp_args->arg = dollar_treatment(env,  tmp_args->arg);
        //tmp_args->arg = quote_slash( tmp_args->arg);
        tmp_args = tmp_args->next;
    }
    tmp_redirections = ptr->redirections;
    while (tmp_redirections != NULL)
    {
        tmp_redirections->redirection_type = dollar_treatment(env,  tmp_redirections->redirection_type);
        //tmp_redirections->redirection_type = quote_slash( tmp_redirections->redirection_type);
        tmp_redirections->redirection_file = dollar_treatment(env,  tmp_redirections->redirection_file);
        //tmp_redirections->redirection_file = quote_slash( tmp_redirections->redirection_file);
        tmp_redirections = tmp_redirections->next;
    }
}
void    purge(char        **env, t_format    *ptr)
{
    if (ptr->pipes == NULL)//no pipes
        cleanse_no_pipes(env, ptr);
    else if (ptr->pipes != NULL)//yes pipes
        cleanse_yes_pipes(env, ptr);
}