#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "./libft/libft.h"
# include "./parse/functions_headerfile.h"

typedef struct s_var
{
	int	sin;
	int	sout;
}				t_var;

int		ft_exec(t_format *ptr, t_node **head);
int		ft_echo(t_arguments *arguments);
int		ft_pwd(void);
int		ft_cd(t_arguments *arguments, t_node **head);
int		ft_exit(t_arguments *arguments);
int		ft_env(t_arguments *arguments, t_node *head);
int		ft_export(t_arguments *arguments, t_node **head);
int		ft_unset(t_arguments *arguments, t_node **head);
int		ft_path(char *command, t_arguments *arguments, t_node *head);
void	ft_free_split(char **split);
int		ft_strcmp(char *s1, char *s2);
int		ft_isabsolute(char *s);
int		ft_ispath(char *s);
char	*ft_join(char const *s1, char const *s2);
void	push_node(t_node **head, char *newdata);
void	print_list(t_node *node);
t_node	*get_envp(char **env);
char	*check_command(char **split, char *cmd);
char	*ft_equal(char	*s1);
int		export_error(char *s, int i);
int		valid_id(char *s);
void	print_export(t_node *node);
void	print_cases(char *s, int ret);
int		check_value(char *s);
void	deletenode(t_node **head, char *pos);
int		arglen(char *s);
int		get_arglen(char *s1, char *s2);
int		check_overwrite(t_node *node, char *s);
int		isequal(char *s);
void	deletelist(t_node **head_ref);
t_node	*copyList(t_node *head);
t_node	*sort_list(t_node *start);
void	swap(t_node *a, t_node *b);
char	**convertlist(t_arguments *node, char *s);
int		ft_listlen(t_arguments *node);
char	**convertenv(t_node *node);
int		ft_envlen(t_node *node);
void	shlvl(t_node **head);
int		check_redirection(t_redirections *redirections);
void	ft_setpipes(t_pipes *pipes, t_node **head);
int		ft_exec_cmd(char *command, t_arguments *arguments,
			t_redirections *redirections, t_node **head);
void	ft_resetio(int sin, int sout);
char	*get_envar(t_node *node, char *s);
void	fd_putstr(char *s1, char *s2, char *s3, char *s4);
int		ft_path_not_forked(char *command, t_arguments *arguments, t_node *head);
int		ft_path_forked(char *command, t_arguments *arguments, t_node *head);
void	pwd_error(void);
void	ft_fetchcmd(char *command, t_arguments *arguments, t_node **head);
void	cmd_error(char *s);
void	path_error(char *s);
char	*getpath(t_node *node);
int		red_error(char *s);
void	ft_close(t_redirections *redirections, int in, int out);
int		oflag(int i);
void	set_lvl(char **s, t_node **head);
int		pipe_len(t_pipes *pipes);
void	ft_duppipes(int i, int len, int fd[][2]);
void	ft_closepipes(int i, int len, int fd[][2]);
void	ft_waitpipes(int len, int *pid);
t_node	*init_shell(char **env, int ac, char **av);
void	init_pwd(t_node **head);
void	handler2(int sig);
void	handler(int sig);

#endif