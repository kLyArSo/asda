#include "functions_headerfile.h"

void	var_freedom(t_var_rep	*data)
{
	free(data->variable_name);
	data->variable_name = NULL;
	free(data->variable_content);
	data->variable_content = NULL;
}

void	var_fetch(t_var_rep		*data, char	*slice, int	i, t_env	*ptr_env)
{
	data->variable_name = fetch_var_name(slice, i);
	data->variable_content = fetch_variable_content(ptr_env,
			data->variable_name);
}

void	set_glob(t_var_rep		*data, char		*slice)
{
	data->variable_name = ft_strdup("?");
	data->variable_content = ft_itoa(g_global.ret);
}

char	*quotes_post_dollar(char	*slice, int		i)
{
	char			*kass;
	char			*str_1;
	char			*str_2;

	str_1 = ft_substr(slice, 0, i - 2);
	str_2 = ft_substr(slice, i, ft_strlen(slice));
	kass = ft_strjoin_dollar_sign(str_1, str_2);
	free(slice);
	return (kass);
}

char	*final_fetch(t_var_rep	*data, char	*slice, int	i, t_env	*ptr_env)
{
	data->dollar_position = i++;
	if (ft_test_char("\'\"", slice[i]) == 1)
		slice = quotes_post_dollar(slice, i);
	else
	{
		if (slice[i] == '?')
			set_glob(data, slice);
		else
			var_fetch(data, slice, i, ptr_env);
		if (my_strcmp(data->variable_name, "") != 0)
			slice = var_replacement(data, slice);
		var_freedom(data);
	}
	return (slice);
}
