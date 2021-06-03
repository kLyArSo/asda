#include "functions_headerfile.h"

char	*fetch_wanted_var(char	*name, t_env	*ptr)
{
	while (ptr != NULL)
	{
		if (strcmp(name, ptr->var_name) == 0)
			return (ft_strdup(ptr->var_content));
		ptr = ptr->next;
	}
	return (NULL);
}

char	*fetch_variable_content(t_env	*ptr, char	*name)
{
	char	*ret;

	ret = fetch_wanted_var(name, ptr);
	if (ret == NULL)
		ret = ft_strdup("");
	return (ret);
}

void	free_env_contens(t_env	*ptr)
{
	while (ptr != NULL)
	{
		free(ptr->var_content);
		free(ptr->var_name);
		ptr = ptr->next;
	}
}

void	free_env_nodes(t_env	*ptr)
{
	t_env	*tmp;

	while (ptr != NULL)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

void	dollar_freedom_1(t_var_rep	*data, t_env	*ptr_env)
{
	free(data);
	data = NULL;
	free_env_contens(ptr_env);
	free_env_nodes(ptr_env);
	ptr_env = NULL;
}
