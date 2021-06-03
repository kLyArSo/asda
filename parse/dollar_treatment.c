#include "functions_headerfile.h"

char	*dollar_treatment(char	**env, char	*slice)
{
	int			i;
	t_var_rep	*data;
	t_env		*ptr_env;

	ptr_env = fetch_all_variables(env);
	i = 0;
	data = malloc(sizeof(t_var_rep));
	if (data == NULL)
		return (NULL);
	while (slice[i] != 0)
	{
		i = find_valid_dollar(slice);
		if (i == -1)
			break ;
		else
			slice = final_fetch(data, slice, i, ptr_env);
	}
	dollar_freedom_1(data, ptr_env);
	return (slice);
}
