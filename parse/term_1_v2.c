#include "functions_headerfile.h"

void	up_key(t_toolbox	*box)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, put_char);
	tputs(tgetstr("dl", NULL), 1, put_char);
	put_strings("minishell~$ ", NULL, NULL, NULL);
	if (box->ptr->previous != NULL)
	{
		box->ptr = box->ptr->previous;
		free(box->str);
		box->str = ft_strdupe(box->ptr->line);
	}
	put_strings(box->str, NULL, NULL, NULL);
}

void	down_key(t_toolbox	*box)
{
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, put_char);
	tputs(tgetstr("dl", NULL), 1, put_char);
	put_strings("minishell~$ ", NULL, NULL, NULL);
	if (box->ptr->next != NULL)
	{
		box->ptr = box->ptr->next;
		free(box->str);
		box->str = ft_strdupe(box->ptr->line);
	}
	if (box->ptr->next == NULL)
	{
		free(box->str);
		box->str = my_calloc(1);
	}
	put_strings(box->str, NULL, NULL, NULL);
}

void	ctrl_d_key(t_toolbox	*box)
{
	if (my_strcmp(box->str, "") == 0)
	{
		tcsetattr(0, TCSANOW, &box->old);
		put_strings("\nexit\n", NULL, NULL, NULL);
		free(box->str);
		free_history();
		exit(g_global.ret);
	}
}

void	update_position(t_toolbox	*box)
{
	while (box->ptr->next != NULL)
		box->ptr = box->ptr->next;
}

void	next_history_node(t_toolbox	*box)
{
	box->ptr->line = box->str;
	box->ptr->next = malloc(sizeof(t_history));
	box->tmp = box->ptr;
	box->ptr = box->ptr->next;
	box->str = my_calloc(1);
	init_history_node_data(box);
	box->ptr->previous = box->tmp;
}
