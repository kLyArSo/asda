#include "functions_headerfile.h"

int	parse_error_check(char	*input, int	i)
{
	if (i == 0 || (input[i] == '|' && input[i + 1] == '\0'))
		return (-1);
	i++;
	if (ft_test_char(";|", input[i]) == 1)
		return (-1);
	while (input[i] != 0 && is_white_space(input[i]) == 1)
		i++;
	if (ft_test_char(";|", input[i]) == 1)
		return (-1);
	i--;
	return (i);
}

int	redirection_error_check(char *input, int i)
{
	int		start;
	int		end;
	char	*str;
	int		counter;

	counter = 0;
	start = i;
	while (input[i] != 0 && ft_test_char("<>", input[i]) == 1)
		i++;
	end = i - 1;
	str = ft_substr(input, start, end);
	if (my_strcmp(">", str) != 0 && my_strcmp(">>", str) != 0
		&& my_strcmp("<", str) != 0 && my_strcmp("<>", str) != 0)
	{
		free(str);
		str = NULL;
		return (-1);
	}
	while (input[i] != 0 && is_white_space(input[i]) == 1)
	{
		i++;
		counter++;
	}
	return (error_suite(counter, input, i, str));
}

int	error_suite(int	counter, char	*input, int	i, char	*str)
{
	free(str);
	if (counter != 0)
	{
		if (input[i] == '\0' || input[i] == ';' || input[i] == '|'
			|| ft_test_char("<>", input[i]) == 1)
			return (-1);
	}
	else if (counter == 0)
	{
		if (input[i] == ';' || input[i] == '\0' || input[i] == '|')
			return (-1);
		if (input[i] == '|')
		{
			while (input[i] != 0 && is_white_space(input[i]) == 1)
				i++;
			if (input[i] == '\0' || ft_test_char("<>", input[i]) == 1)
				return (-1);
		}
	}
	return (i - 1);
}
