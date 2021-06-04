#include "functions_headerfile.h"

int	test_c(char	c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'))
		return (1);
	return (0);
}

ssize_t	find_valid_dollar(char	*slice)
{
	int		i;

	i = 0;
	while (slice[i] != 0)
	{
		while (slice[i] != 0
			&& ((ft_test_char("\'$", slice[i]) == 0)
				|| (ft_test_char("\'$", slice[i]) == 1
					&& back_slash_presence(slice, i - 1) == 1)))
			i++;
		if (ft_test_char("\'", slice[i]) == 1)
			i = skip_quotes(slice, i) + 1;
		if (slice[i] == '$' && slice[i + 1] == '$')
			rep_dollar(slice, i);
		if (slice[i] == '$' && back_slash_presence(slice, i - 1) == 0)
			return (i);
		if (slice[i] != 0)
			i++;
	}
	return (-1);
}

char	*fetch_var_name(char *slice, int i)
{
	int		start;
	int		end;
	char	*result;

	start = i;
	while (slice[i] != 0 && test_c(slice[i]) == 1)
		i++;
	end = i - 1;
	result = ft_substr(slice, start, end);
	return (result);
}

char	*ft_strjoin_dollar_sign(char	*s1, char	*s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i] != 0)
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = 0;
	free(s1);
	free(s2);
	return (result);
}

char	*var_replacement(t_var_rep	*data, char		*slice)
{
	char	*tmp_1;
	char	*tmp_2;

	tmp_1 = ft_substr(slice, 0, data->dollar_position - 1);
	tmp_2 = ft_substr(slice, data->dollar_position
			+ ft_strlen(data->variable_name) + 1, ft_strlen(slice));
	tmp_1 = ft_strjoin_dollar_sign(tmp_1, ft_strdup(data->variable_content));
	tmp_1 = ft_strjoin_dollar_sign(tmp_1, tmp_2);
	free(slice);
	return (tmp_1);
}
