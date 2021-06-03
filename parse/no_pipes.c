#include "functions_headerfile.h"

void	free_arg_content(t_format	*ptr)
{
	t_arguments	*tmp_1;

	tmp_1 = ptr->arguments;
	while (tmp_1 != NULL)
	{
		free(tmp_1->arg);
		tmp_1 = tmp_1->next;
	}
}

void	free_red_content(t_format	*ptr)
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

void	no_pipes_free(t_format	*ptr)
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
	if (ptr->arguments != NULL)
	{
		free_arg_content(ptr);
		free_arg_nodes(ptr);
	}
	if (ptr->redirections != NULL)
	{
		free_red_content(ptr);
		free_red_nodes(ptr);
	}
	if (ptr->sliced_line != NULL)
		free_sliced_nodes(ptr);
}
