#include "functions_headerfile.h"

void	*o(t_format	*p, t_var_rep	*d, t_env	*pe, t_arguments	*ap)
{
	free_contenta(d);
	while (ap != NULL)
	{
		if (ap->arg[0] == '$')
		{
			fetch_contenta(d, pe, p);
			if (my_strcmp(d->variable_content, "") != 0)
			{
				s3(p, d, pe, ap);
				return (NULL);
			}
			free_contenta(d);
		}
		else if (ap->arg[0] != '$')
		{
			s4(p, d, pe, ap);
			return (NULL);
		}
		ap = ap->next;
	}
	return ("done");
}

void	*dollar_exceptions_no_pipes(char	**env, t_format	*ptr)
{
	t_var_rep	*data;
	t_arguments	*arg_ptr;
	char		*kass;
	t_env		*ptr_env;

	ptr_env = fetch_all_variables(env);
	data = malloc(sizeof(t_var_rep));
	arg_ptr = ptr->arguments;
	if (ptr->command != NULL && ptr->command[0] == '$'
		&& ptr->command[1] != '\0')
	{
		fetch_contenta(data, ptr_env, ptr);
		if (my_strcmp(data->variable_content, "") == 0)
		{
			if (o(ptr, data, ptr_env, arg_ptr) == NULL)
				return (NULL);
		}
		else
			fetch_contenta(data, ptr_env, ptr);
	}
	last_freea(data, ptr_env);
	return (NULL);
}

void	redas(t_redirections	*tmp_redirections, char **env)
{
	while (tmp_redirections != NULL)
	{
		tmp_redirections->redirection_type = dollar_treatment(env,
				tmp_redirections->redirection_type);
		tmp_redirections->redirection_type = quote_slash(
				tmp_redirections->redirection_type);
		tmp_redirections->redirection_file = dollar_treatment(env,
				tmp_redirections->redirection_file);
		tmp_redirections->redirection_file = quote_slash(
				tmp_redirections->redirection_file);
		tmp_redirections = tmp_redirections->next;
	}
}

void	cleanse_no_pipes(char	**env, t_format	*ptr)
{
	t_arguments		*tmp_args;
	t_redirections	*tmp_redirections;

	dollar_exceptions_no_pipes(env, ptr);
	if (ptr->command != NULL)
	{
		ptr->command = dollar_treatment(env, ptr->command);
		ptr->command = quote_slash(ptr->command);
	}
	tmp_args = ptr->arguments;
	while (tmp_args != NULL)
	{
		tmp_args->arg = dollar_treatment(env, tmp_args->arg);
		tmp_args->arg = quote_slash(tmp_args->arg);
		tmp_args = tmp_args->next;
	}
	tmp_redirections = ptr->redirections;
	redas(tmp_redirections, env);
}
