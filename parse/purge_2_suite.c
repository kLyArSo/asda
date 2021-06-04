#include "functions_headerfile.h"

void	s3(t_format	*p, t_var_rep	*d, t_env	*pe, t_arguments	*ap)
{
	char	*kass;

	kass = p->command;
	p->command = ap->arg;
	ap->arg = kass;
	free(d->variable_name);
	free(d->variable_content);
	free_env_contens(pe);
	free_env_nodes(pe);
	pe = NULL;
	free(d);
}

void	s4(t_format	*p, t_var_rep	*d, t_env	*pe, t_arguments	*ap)
{
	char	*kass;

	kass = p->command;
	p->command = ap->arg;
	ap->arg = kass;
	free_env_contens(pe);
	free_env_nodes(pe);
	pe = NULL;
	free(d);
}

void	free_contenta(t_var_rep	*data)
{
	free(data->variable_name);
	free(data->variable_content);
}

void	fetch_contenta(t_var_rep	*data, t_env	*ptr_env, t_format	*ptr)
{
	data->variable_name = fetch_var_name(ptr->command, 1);
	data->variable_content = fetch_variable_content(ptr_env,
			data->variable_name);
}

void	last_freea(t_var_rep	*data, t_env	*ptr_env)
{
	free(data);
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
}
