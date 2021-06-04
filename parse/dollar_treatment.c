#include "functions_headerfile.h"

void	rep_dollar(char	*slice, int i)
{
	int	x;

	x = 1;
	while (slice[i] == '$' && slice[i + 1] == '$')
	{
		if (x == 1)
		{
			slice[i] = '?';
			x = 2;
		}
		else if (x == 2)
		{
			slice[i] = '!';
			x = 1;
		}
		i++;
	}
}

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
