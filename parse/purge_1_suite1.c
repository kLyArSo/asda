#include "functions_headerfile.h"

void	*x_l(t_pipes	*ptr, t_var_rep	*d, t_env	*pe, t_arguments	*ap)
{
	free_contents(d);
	while (ap != NULL)
	{
		if (ap->arg[0] == '$')
		{
			fetch_contents(d, pe, ptr);
			if (my_strcmp(d->variable_content, "") != 0)
			{
				s1(ptr, d, pe, ap);
				return (NULL);
			}
			free_contents(d);
		}
		else if (ap->arg[0] != '$')
		{
			s2(ptr, d, pe, ap);
			return (NULL);
		}
		ap = ap->next;
	}
	return ("done");
}

void	*x(t_pipes	*p, t_var_rep	*d, t_env	*pe, t_arguments	*ap)
{
	if (my_strcmp(d->variable_content, "") == 0)
	{
		if (x_l(p, d, pe, ap) == NULL)
			return (NULL);
	}
	else
		free_contents(d);
	return ("done");
}

void	*dollar_exception_yes_pipes(char	**env, t_format	*rtp)
{
	t_var_rep	*data;
	t_arguments	*arg_ptr;
	t_pipes		*ptr;
	t_env		*ptr_env;

	ptr_env = fetch_all_variables(env);
	data = malloc(sizeof(t_var_rep));
	ptr = rtp->pipes;
	while (ptr != NULL)
	{
		arg_ptr = ptr->arguments;
		if (ptr->command != NULL
			&& ptr->command[0] == '$' && ptr->command[1] != '\0')
		{
			fetch_contents(data, ptr_env, ptr);
			if (x(ptr, data, ptr_env, arg_ptr) == NULL)
				return (NULL);
		}
		ptr = ptr->next;
	}
	last_free(data, ptr_env);
	return (NULL);
}

void	treat_reda(t_redirections	*tmp_redirections, char **env)
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

void	purge_process(t_pipes	*tmp_pipes, char	**env)
{
	t_arguments		*tmp_args;
	t_redirections	*tmp_redirections;

	if (tmp_pipes->command != NULL)
	{
		tmp_pipes->command = dollar_treatment(env, tmp_pipes->command);
		tmp_pipes->command = quote_slash(tmp_pipes->command);
	}
	tmp_args = tmp_pipes->arguments;
	while (tmp_args != NULL)
	{
		tmp_args->arg = dollar_treatment(env, tmp_args->arg);
		tmp_args->arg = quote_slash(tmp_args->arg);
		tmp_args = tmp_args->next;
	}
	tmp_redirections = tmp_pipes->redirections;
	treat_reda(tmp_pipes->redirections, env);
}
