#include "functions_headerfile.h"

void	free_sliced_contents(t_linedata	*ptr)
{
	while (ptr != NULL)
	{
		free(ptr->slice);
		ptr->slice = NULL;
		ptr = ptr->next;
	}
}

void	free_sliced_nodes(t_format	*ptr)
{
	t_linedata	*tmp_1;
	t_linedata	*tmp_2;

	tmp_1 = ptr->sliced_line;
	while (tmp_1 != NULL)
	{
		tmp_2 = tmp_1->next;
		free(tmp_1);
		tmp_1 = tmp_2;
	}
	ptr->sliced_line = NULL;
}

void	free_red_nodes(t_format	*ptr)
{
	t_redirections	*tmp_1;
	t_redirections	*tmp_2;

	tmp_1 = ptr->redirections;
	while (tmp_1 != NULL)
	{
		tmp_2 = tmp_1->next;
		free(tmp_1);
		tmp_1 = tmp_2;
	}
	ptr->redirections = NULL;
}

void	free_arg_nodes(t_format	*ptr)
{
	t_arguments	*tmp_1;
	t_arguments	*tmp_2;

	tmp_1 = ptr->arguments;
	while (tmp_1 != NULL)
	{
		tmp_2 = tmp_1->next;
		free(tmp_1);
		tmp_1 = tmp_2;
	}
	ptr->arguments = NULL;
}
