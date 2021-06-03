#include "functions_headerfile.h"

void	*fetch_pipes(t_format	*ptr, int	start, int	i)
{
	t_pipes	*tmp;

	ptr->pipes = malloc(sizeof(t_pipes));
	tmp = ptr->pipes;
	while (ptr->line[i] != 0)
	{
		i = skips(ptr, i);
		if (ptr->line[i] == '|')
		{
			ptr->pipes = f2(ptr, &start, i);
			if (ptr->pipes == NULL)
				return (NULL);
		}
		ft_end(ptr, &i, start);
	}
	ptr->pipes = tmp;
	return ("done");
}

void	assignments(t_format	*ptr)
{
	ptr->pre_pipe_line = ptr->line;
	ptr->sliced_line = split_id(ptr->pre_pipe_line);
	ptr->command = fetch_command(ptr->sliced_line);
	ptr->redirections = fetch_reds(ptr->sliced_line, NULL, 0);
	ptr->arguments = fetch_arguments(ptr->sliced_line, NULL, 0);
	ptr->pipes = NULL;
}

void	*pipe_split(t_format	*ptr)
{
	while (ptr != NULL)
	{
		ptr->pipe_presence = pipe_presence(ptr->line);
		if (ptr->pipe_presence == 0)
			assignments(ptr);
		else
		{
			ptr->pre_pipe_line = NULL;
			if (fetch_pipes(ptr, 0, 0) == NULL)
				return (NULL);
		}
		ptr = ptr->next;
	}
	return ("done");
}
