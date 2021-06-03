#include "functions_headerfile.h"

void	free_red_contents_yp(t_pipes	*ptr)
{
	t_redirections	*tmp_1;

	tmp_1 = ptr->redirections;
	while (tmp_1 != NULL)
	{
		free(tmp_1->redirection_file);
		tmp_1->redirection_file = NULL;
		free(tmp_1->redirection_type);
		tmp_1->redirection_type = NULL;
		tmp_1 = tmp_1->next;
	}
}

void	yes_while(t_pipes	*ptr)
{
	if (ptr->line != NULL)
	{
		free(ptr->line);
		ptr->line = NULL;
	}
	if (ptr->command != NULL)
	{
		free(ptr->command);
		ptr->command = NULL;
	}
	if (ptr->sliced_line != NULL)
		free_sliced_nodes_yp(ptr);
	if (ptr->arguments != NULL)
	{
		free_arg_contents_yp(ptr);
		free_arg_nodes_yp(ptr);
	}
	if (ptr->redirections != NULL)
	{
		free_red_contents_yp(ptr);
		free_red_nodes_yp(ptr);
	}
}

void	yes_pipes_free(t_format	*tmp)
{
	t_pipes	*ptr;
	t_pipes	*temp;

	ptr = tmp->pipes;
	while (ptr != NULL)
	{
		yes_while(ptr);
		ptr = ptr->next;
	}
	ptr = tmp->pipes;
	while (ptr != NULL)
	{
		temp = ptr->next;
		free(ptr);
		ptr = temp;
	}
	ptr = NULL;
}
