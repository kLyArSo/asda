#include "functions_headerfile.h"

void	swap_n_free_0(t_var_rep	*data, t_pipes	*ptr, t_arguments	*arg_ptr, t_env	*ptr_env)
{
	char *kass;

	kass = ptr->command;
	ptr->command = arg_ptr->arg;
	arg_ptr->arg = kass;
	free(data->variable_name);
	free(data->variable_content);
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
	ptr_env = NULL;
	free(data);
}

void	swap_n_free_1(t_var_rep	*data, t_pipes	*ptr, t_arguments	*arg_ptr, t_env	*ptr_env)
{
	char *kass;

	kass = ptr->command;
	ptr->command = arg_ptr->arg;
	arg_ptr->arg = kass;
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
	ptr_env = NULL;
	free(data);
}

void    *treatment(t_var_rep	*data, t_pipes	*ptr, t_arguments	*arg_ptr, t_env	*ptr_env)
{
    free(data->variable_name);
    free(data->variable_content);
	while (arg_ptr != NULL)
	{
		if (arg_ptr->arg[0] == '$')
		{
			data->variable_name = fetch_var_name(arg_ptr->arg, 1);
			data->variable_content = fetch_variable_content(ptr_env, data->variable_name);
			if (my_strcmp(data->variable_content, "") != 0)
			{
				swap_n_free_0(data, ptr, arg_ptr, ptr_env);
				return (NULL);
			}
			free(data->variable_name);
			free(data->variable_content);
		}
		else if (arg_ptr->arg[0] != '$')
		{
			swap_n_free_1(data, ptr, arg_ptr, ptr_env);
			return (NULL);
		}
		arg_ptr = arg_ptr->next;
	}
	return ("done");
}

void        *dollar_exception_yes_pipes(char        **env, t_format    *rtp)
{
	t_var_rep       *data;
	t_arguments     *arg_ptr;
	t_pipes         *ptr;
	t_env           *ptr_env;

	ptr_env = fetch_all_variables(env);
	data = malloc(sizeof(t_var_rep));
	ptr = rtp->pipes;
	while (ptr != NULL)
	{
		arg_ptr = ptr->arguments;
		if (ptr->command != NULL && ptr->command[0] == '$' && ptr->command[1] != '\0')
		{
			data->variable_name = fetch_var_name(ptr->command, 1);
            data->variable_content = fetch_variable_content(ptr_env, data->variable_name);
			if (my_strcmp(data->variable_content, "") == 0)
			{
				if (treatment(data, ptr, arg_ptr, ptr_env) == NULL)
					return (NULL);
			}
		}
        else
        {
            free(data->variable_name);
            free(data->variable_content);
        }
		ptr = ptr->next;
	}
	free(data);
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
	ptr_env = NULL;
	return (NULL);
}

void	mean_while_yes(t_pipes	*tmp_pipes, char	**env)
{
	t_arguments     *tmp_args;
	t_redirections  *tmp_redirections;
	
	if (tmp_pipes->command != NULL)
	{
		tmp_pipes->command = dollar_treatment(env, tmp_pipes->command);
		tmp_pipes->command = quote_slash(tmp_pipes->command);
	}
	tmp_args = tmp_pipes->arguments;
	while (tmp_args != NULL)
	{
		tmp_args->arg = dollar_treatment(env, tmp_args->arg);
		tmp_args->arg = quote_slash( tmp_args->arg);
		tmp_args = tmp_args->next;
	}
	tmp_redirections = tmp_pipes->redirections;
	while (tmp_redirections != NULL)
	{
		tmp_redirections->redirection_type = dollar_treatment(env, tmp_redirections->redirection_type);
		tmp_redirections->redirection_type = quote_slash(tmp_redirections->redirection_type);
		tmp_redirections->redirection_file = dollar_treatment(env, tmp_redirections->redirection_file);
		tmp_redirections->redirection_file = quote_slash(tmp_redirections->redirection_file);
		tmp_redirections = tmp_redirections->next;
	}
}

void    cleanse_yes_pipes(char        **env, t_format    *ptr)
{
	t_pipes         *tmp_pipes;
	t_arguments     *tmp_args;
	t_redirections  *tmp_redirections;

	tmp_pipes = ptr->pipes;
	dollar_exception_yes_pipes(env, ptr);
	while(tmp_pipes != NULL)
	{
		mean_while_yes(tmp_pipes, env);
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

void	swap_n_free_00(t_var_rep	*data, t_format	*ptr, t_arguments	*arg_ptr, t_env	*ptr_env)
{
	char *kass;

	kass = ptr->command;
	ptr->command = arg_ptr->arg;
	arg_ptr->arg = kass;
	free(data->variable_name);
	free(data->variable_content);
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
	ptr_env = NULL;
	free(data);
}
void	swap_n_free_11(t_var_rep	*data, t_format	*ptr, t_arguments	*arg_ptr, t_env	*ptr_env)
{
	char *kass;

	kass = ptr->command;
	ptr->command = arg_ptr->arg;
	arg_ptr->arg = kass;
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
	ptr_env = NULL;
	free(data);
}
void	*treat(t_var_rep	*data, t_arguments	*arg_ptr, t_format	*ptr, t_env	*ptr_env)
{
	char	*kass;

	free(data->variable_name);
	free(data->variable_content);
	while (arg_ptr != NULL)
	{
		if (arg_ptr->arg[0] == '$')
		{
			data->variable_name = fetch_var_name(arg_ptr->arg, 1);
			data->variable_content = fetch_variable_content(ptr_env, data->variable_name);
			if (my_strcmp(data->variable_content, "") != 0)
			{
				swap_n_free_00(data, ptr, arg_ptr, ptr_env);
				return (NULL);
			}
			free(data->variable_name);
			free(data->variable_content);
		}
		else if (arg_ptr->arg[0] != '$')
		{
			swap_n_free_11(data, ptr, arg_ptr, ptr_env);
			return (NULL);
		}
		arg_ptr = arg_ptr->next;
	}
	return ("done");
}

void        *dollar_exceptions_no_pipes(char        **env, t_format    *ptr)
{
	t_var_rep       *data;
	t_arguments     *arg_ptr;
	char            *kass;
	t_env           *ptr_env;
	ptr_env = fetch_all_variables(env);
	data = malloc(sizeof(t_var_rep));
	arg_ptr = ptr->arguments;

	if (ptr->command != NULL && ptr->command[0] == '$' && ptr->command[1] != '\0')
	{
		data->variable_name = fetch_var_name(ptr->command, 1);
		data->variable_content = fetch_variable_content(ptr_env, data->variable_name);
		if (my_strcmp(data->variable_content, "") == 0)
		{
			if (treat(data, arg_ptr, ptr, ptr_env) == NULL)
				return (NULL);
		}
		else
		{
			free(data->variable_name);
			free(data->variable_content);
		}
	}
	free(data);
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
	ptr_env = NULL;
	return (NULL);
}

void	mean_while_no(t_format    *ptr, char **env)
{
	t_arguments     *tmp_args;
	t_redirections  *tmp_redirections;

	if (ptr->command != NULL)
	{
		ptr->command = dollar_treatment(env, ptr->command);
		ptr->command = quote_slash(ptr->command);
	}
	tmp_args = ptr->arguments;
	while (tmp_args != NULL)
	{
		tmp_args->arg = dollar_treatment(env, tmp_args->arg);
		tmp_args->arg = quote_slash( tmp_args->arg);
		tmp_args = tmp_args->next;
	}
	tmp_redirections = ptr->redirections;
	while (tmp_redirections != NULL)
	{
		tmp_redirections->redirection_type = dollar_treatment(env, tmp_redirections->redirection_type);
		tmp_redirections->redirection_type = quote_slash( tmp_redirections->redirection_type);
		tmp_redirections->redirection_file = dollar_treatment(env, tmp_redirections->redirection_file);
		tmp_redirections->redirection_file = quote_slash( tmp_redirections->redirection_file);
		tmp_redirections = tmp_redirections->next;
	}
}

void    cleanse_no_pipes(char        **env, t_format    *ptr)
{
	dollar_exceptions_no_pipes(env, ptr);
	mean_while_no(ptr, env);
}

void    purge(char        **env, t_format    *ptr)
{
	if (ptr->pipes == NULL)//no pipes
		cleanse_no_pipes(env, ptr);
	else if (ptr->pipes != NULL)//yes pipes
		cleanse_yes_pipes(env, ptr);
}
