#include "functions_headerfile.h"

void	*enter_key(t_toolbox	*box, t_node	**head)
{
	if (my_strcmp(box->str, "") != 0)
	{
		box->i = all_sp(box->str);
		if (box->ptr->next != NULL)
			update_position(box);
		if (box->i == 0)
			full_ws_niet(box, head);
		else
		{
			next_history_node(box);
			put_strings("\nminishell~$ ", NULL, NULL, NULL);
		}
	}
	else if (my_strcmp(box->str, "") == 0)
		put_strings("\nminishell~$ ", NULL, NULL, NULL);
	return ("done");
}
