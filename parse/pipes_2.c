#include "functions_headerfile.h"

t_redirections	*fetch_reds(t_linedata	*d, t_redirections	*r, int	c)
{
	t_redirections	*ptr;

	while (1)
	{
		if (d->redirection == 1)
		{
			if (c == 0)
			{
				c = 1;
				ptr = malloc(sizeof(t_redirections));
				r = ptr;
				d = a_s(d, ptr);
			}
			else if (c == 1)
			{
				ptr->next = malloc(sizeof(t_redirections));
				ptr = ptr->next;
				d = a_s(d, ptr);
			}
		}
		d = d->next;
		if (d == NULL)
			break ;
	}
	return (r);
}

t_pipes	*f2(t_format	*ptr, int	*start, int	i)
{
	ptr->pipes->line = trim_spaces(ft_substr(ptr->line, *start, i - 1));
	ptr->pipes->sliced_line = split_id(ptr->pipes->line);
	ptr->pipes->command = fetch_command(ptr->pipes->sliced_line);
	ptr->pipes->redirections = fetch_reds(ptr->pipes->sliced_line, NULL, 0);
	ptr->pipes->arguments = fetch_arguments(ptr->pipes->sliced_line, NULL, 0);
	ptr->pipes->next = malloc(sizeof(t_pipes));
	*start = i + 1;
	return (ptr->pipes->next);
}

void	f3(t_format	*ptr, int	start, int	i)
{
	ptr->pipes->line = trim_spaces(ft_substr(ptr->line, start, i - 1));
	ptr->pipes->sliced_line = split_id(ptr->pipes->line);
	ptr->pipes->command = fetch_command(ptr->pipes->sliced_line);
	ptr->pipes->redirections = fetch_reds(ptr->pipes->sliced_line, NULL, 0);
	ptr->pipes->arguments = fetch_arguments(ptr->pipes->sliced_line, NULL, 0);
	ptr->pipes->next = NULL;
}

int	skips(t_format	*ptr, int	i)
{
	while (ptr->line[i] != 0
		&& (ft_test_char("\'\"|", ptr->line[i]) == 0
			|| (ft_test_char("\'\"|", ptr->line[i]) == 1
				&& back_slash_presence(ptr->line, i - 1) == 1)))
		i++;
	if (ft_test_char("\'\"", ptr->line[i]) == 1)
		i = skip_quotes(ptr->line, i);
	return (i);
}

void	ft_end(t_format	*ptr, int	*i, int	start)
{
	int	j;

	j = *i;
	if (ptr->line[j] != 0)
		j++;
	if (ptr->line[j] == 0)
		f3(ptr, start, j);
	*i = j;
}
