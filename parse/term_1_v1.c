#include "functions_headerfile.h"

void	*init_all(t_toolbox	*box)
{
	box->formaptr = malloc(sizeof(t_format));
	if (box->formaptr == NULL)
		return (NULL);
	box->ptr = malloc(sizeof(t_history));
	if (box->ptr == NULL)
	{
		free(box->formaptr);
		box->formaptr = NULL;
		return (NULL);
	}
	box->str = my_calloc(1);
	if (box->str == NULL)
	{
		free(box->formaptr);
		box->formaptr = NULL;
		free(box->ptr);
		box->ptr = NULL;
		return (NULL);
	}
	box->ptr->previous = NULL;
	box->ptr->next = NULL;
	box->ptr->line = NULL;
	tcgetattr(0, &box->old);
	tgetent(getenv("TERM"), NULL);
	return ("done");
}

void	put_strings(char	*s1, char	*s2, char	*s3, char	*s4)
{
	if (s1 != NULL)
		write(1, s1, ft_strlen(s1));
	if (s2 != NULL)
		write(1, s2, ft_strlen(s2));
	if (s3 != NULL)
		write(1, s3, ft_strlen(s3));
	if (s4 != NULL)
		write(1, s4, ft_strlen(s4));
}

void	init_history_node_data(t_toolbox	*box)
{
	box->ptr->previous = NULL;
	box->ptr->next = NULL;
	box->ptr->line = NULL;
}

void	printable_key(t_toolbox	*box)
{
	box->str = j_oin(box->str, box->ascii);
	write(1, &box->ascii, 1);
}

void	delete_key(t_toolbox	*box)
{
	if (ft_strlen(box->str) > 0)
	{
		box->str = delete_char(box->str);
		tputs(tgetstr("le", NULL), 1, put_char);
		tputs(tgetstr("dc", NULL), 1, put_char);
	}
}
