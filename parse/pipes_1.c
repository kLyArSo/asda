#include "functions_headerfile.h"

int	pipe_presence(char	*input)
{
	int		i;

	i = 0;
	while (input[i] != 0)
	{
		while (input[i] != 0
			&& (ft_test_char("\'\"|", input[i]) == 0
				|| (ft_test_char("\'\"|", input[i]) == 1
					&& back_slash_presence(input, i - 1) == 1)))
			i++;
		if (input[i] == '|')
			return (1);
		else if (ft_test_char("\'\"", input[i]) == 1)
			i = skip_quotes(input, i);
		if (input[i] != 0)
			i++;
	}
	return (0);
}

char	*fetch_command(t_linedata	*data)
{
	while (data != NULL)
	{
		if (data->command == 1)
			return (data->slice);
		data = data->next;
	}
	return (NULL);
}

t_arguments	*f_16(t_arguments	*ptr, t_linedata	*data)
{
	ptr->next = malloc(sizeof(t_arguments));
	ptr = ptr->next;
	ptr->arg = data->slice;
	ptr->next = NULL;
	return (ptr);
}

t_arguments	*fetch_arguments(t_linedata	*data, t_arguments	*ret, int	counter)
{
	t_arguments	*ptr;

	while (data != NULL)
	{
		if (data->command == 0 && data->argument == 1)
		{
			if (counter == 0)
			{
				counter++;
				ptr = malloc(sizeof(t_arguments));
				ret = ptr;
				ptr->arg = data->slice;
				ptr->next = NULL;
			}
			else if (counter == 1)
				ptr = f_16(ptr, data);
		}
		data = data->next;
	}
	return (ret);
}

t_linedata	*a_s(t_linedata	*data, t_redirections	*ptr)
{
	ptr->redirection_type = data->slice;
	data = data->next;
	ptr->redirection_file = data->slice;
	ptr->next = NULL;
	return (data);
}
