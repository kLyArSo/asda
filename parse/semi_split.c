#include "functions_headerfile.h"

void	*semicolon_split(t_format	*ptr, char	*input)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (input[i] != 0)
	{
		skip_un(input, i, &i);
		if (input[i] == ';')
			ptr = fetch(ptr, input, &start, i);
		if (input[i] != 0)
			i++;
		if (input[i] == 0)
		{
			ptr->line = trim_spaces(ft_substr(input, start, i - 1));
			if (ptr->line == NULL)
				return (NULL);
			ptr->next = NULL;
		}
	}
	return ("done");
}

char	*ft_substr_1(char	*str, int	start, int	end)
{
	int		i;
	char	*result;

	i = 0;
	if (str == NULL)
		return (NULL);
	result = my_calloc(end - start + 2);
	while (start <= end)
	{
		result[i] = str[start];
		start++;
		i++;
	}
	free(str);
	return (result);
}

char	*last_check(t_toolbox	*box)
{
	int	start;
	int	end;

	start = 0;
	if (box->str == NULL)
		return (NULL);
	while (box->str[start] != 0
		&& is_white_space(box->str[start]) == 1)
		start++;
	end = ft_strlen(box->str) - 1;
	while (end >= 0
		&& is_white_space(box->str[end]) == 1
		&& back_slash_presence(box->str, end - 1) == 0)
		end--;
	if (box->str[end] == ';'
		&& back_slash_presence(box->str, end - 1) == 0)
		end--;
	box->str = ft_substr_1(box->str, start, end);
	return ("done");
}
