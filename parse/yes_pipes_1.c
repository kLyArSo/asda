#include "functions_headerfile.h"

void	free_sliced_nodes_yp(t_pipes	*ptr)
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

void	free_arg_nodes_yp(t_pipes	*ptr)
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

void	free_red_nodes_yp(t_pipes	*ptr)
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

void	free_arg_contents_yp(t_pipes	*ptr)
{
	t_arguments	*tmp_1;

	tmp_1 = ptr->arguments;
	while (tmp_1 != NULL)
	{
		free(tmp_1->arg);
		tmp_1 = tmp_1->next;
	}
}
