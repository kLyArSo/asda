#include "./minishell.h"

void    shlvl(t_node **head)
{
    int lvl;
    char **s;
    char *shlvl;
    t_node *tmp;

    lvl = 1;
    tmp = *head;
    while(tmp != NULL)
    {
        s = ft_split(tmp->data, '=');
        if (ft_strcmp(s[0], "SHLVL") == 0)
        {
            lvl += ft_atoi(s[1]);
            free(s[1]);
            s[1] = ft_itoa(lvl);
            shlvl = ft_strjoin("SHLVL=", s[1]);
            deletenode(head, "SHLVL");
            push_node(head, shlvl);
            free(shlvl);
            ft_free_split(s);
            return ;
        }
        else
            ft_free_split(s);
        tmp = tmp->next;
        if (tmp == NULL)
            push_node(head, "SHLVL=1");
    }
}

void    *full_ws_niet(t_toolbox     *box, t_node    **head)
{
	box->check = parse(box);
	if (my_strcmp(box->check, "Unmatched_Quotes") == 0
	|| my_strcmp(box->check, "Back_slash_Error") == 0
    || my_strcmp(box->check, "Redirection_error") == 0
	|| my_strcmp(box->check, "Syntax_error") == 0)
	{
        put_strings("\n",box->check,"\nminishell~$ ",NULL);
		free(box->check);
        box->check = NULL;
        next_history_node(box);
	}
	else
	{ 
        write(1, "\n", 1);
		ft_exec(box->formaptr, head);
		//print_da(box->formaptr);
        free_tformat();
        next_history_node(box);
        put_strings("minishell~$ ",NULL,NULL,NULL);
	}
    return ("done");
}

void handler(int sig)
{
    if (g_global.forked == 1)
    {
        g_global.ret = 1;
        put_strings("\nminishell~$ ",NULL,NULL,NULL);
        free(g_global.box->str);
        g_global.box->str = NULL;
        g_global.box->str = my_calloc(1);
    }
    else if (g_global.forked == 0) //cat
    {
        g_global.ret = 130;
        ft_putchar_fd('\n', 1);
    }
}

void    handler2(int sig)
{
	if (g_global.forked == 0)
    {
        g_global.ret = 131;
        ft_putendl_fd("Quit: 3", 2);
        g_global.forked = 1;
    }
}

void    init_pwd(t_node **head)
{
    char *cwd;
    char *tmp;
    
    cwd = getcwd(NULL, 0);
    tmp = ft_strjoin("PWD=", cwd);
    if (check_overwrite(*head, "PWD"))
        deletenode(head, "PWD");
    push_node(head, tmp);
    if (check_overwrite(*head, "OLDPWD"))
        deletenode(head, "OLDPWD");
    push_node(head, "OLDPWD");
    free(cwd);
    free(tmp);
}


t_node      *init_shell(char        **env)
{
    t_node  *head;
    head = get_envp(env);
    shlvl(&head);
    init_pwd(&head);
    g_global.forked = 1;
    signal(SIGINT, handler);
    signal(SIGQUIT, handler2);
    return (head);
}

t_toolbox   *parse_init()
{
    t_toolbox   *box;

    box = malloc(sizeof(t_toolbox));
    if (box == NULL || init_all(box) == NULL)
        return (NULL);
    g_global.box = box;
    return (box);
}

int     main(int    argc, char      **argv, char        **env)
{
    t_node  *head;
    t_toolbox   *box;

    head = init_shell(env);
    box = parse_init();
    if (box == NULL)
        return (1);
    put_strings("minishell~$ ",NULL,NULL,NULL);

    while (1)
    {
		box->ascii = fetch_char(&box->old);
		if (box->ascii >= 32 && box->ascii <= 126)//all printable chars
            printable_key(box);
		else if (box->ascii == DELETE_KEY)//delete char
            delete_key(box);
		else if (box->ascii == UP_KEY)
            up_key(box);
		else if (box->ascii == DOWN_KEY)
            down_key(box);
		else if (box->ascii == CTRL_D)
            ctrl_d_key(box);
		else if (box->ascii == ENTER_KEY)//enter
        {
	        tcsetattr(0, TCSANOW, &box->old);
            enter_key(box, &head);
        }
    }
    return (0);
}
