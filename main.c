#include "./minishell.h"

void	*full_ws_niet(t_toolbox	*box, t_node	**head)
{
	box->check = parse(box);
	if (my_strcmp(box->check, "Unmatched_Quotes") == 0
		|| my_strcmp(box->check, "Back_slash_Error") == 0
		|| my_strcmp(box->check, "Redirection_error") == 0
		|| my_strcmp(box->check, "Syntax_error") == 0)
	{
		put_strings("\n", box->check, "\nminishell~$ ", NULL);
		free(box->check);
		box->check = NULL;
		next_history_node(box);
	}
	else
	{
		write(1, "\n", 1);
		ft_exec(box->formaptr, head);
		free_tformat();
		next_history_node(box);
		put_strings("minishell~$ ", NULL, NULL, NULL);
	}
	return ("done");
}

t_toolbox	*parse_init(void)
{
	t_toolbox	*box;

	box = malloc(sizeof(t_toolbox));
	if (box == NULL || init_all(box) == NULL)
		return (NULL);
	g_global.box = box;
	return (box);
}

int	main(int argc, char **argv, char **env)
{
	t_node		*head;
	t_toolbox	*box;

	head = init_shell(env, argc, argv);
	box = parse_init();
	if (box == NULL)
		return (1);
	put_strings("minishell~$ ", NULL, NULL, NULL);
	while (1)
	{
		box->ascii = fetch_char(&box->old);
		if (box->ascii >= 32 && box->ascii <= 126)
			printable_key(box);
		else if (box->ascii == DELETE_KEY)
			delete_key(box);
		else if (box->ascii == UP_KEY)
			up_key(box);
		else if (box->ascii == DOWN_KEY)
			down_key(box);
		else if (box->ascii == CTRL_D)
			ctrl_d_key(box);
		else if (box->ascii == ENTER_KEY)
			enter_key(box, &head);
	}
	return (0);
}
