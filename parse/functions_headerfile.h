#ifndef FUNCTIONS_HEADERFILE_H
# define FUNCTIONS_HEADERFILE_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <termios.h>
# include <termcap.h>
# define UP_KEY 183
# define DOWN_KEY 184
# define ENTER_KEY 10
# define DELETE_KEY 127
# define CTRL_D 4

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}				t_node;

typedef struct s_history
{
	struct s_history	*previous;
	char				*line;
	struct s_history	*next;
}				t_history;

typedef struct s_bag
{
	int	i;
	int	start;
	int	cmd_check;
}				t_bag;

typedef struct s_env
{
	char			*var_name;
	char			*var_content;
	struct s_env	*next;
}				t_env;

typedef struct s_linedata
{
	char				*slice;
	int					command;
	int					argument;
	int					redirection;
	int					redirection_file;
	struct s_linedata	*next;
}				t_linedata;

typedef struct s_redirections
{
	char					*redirection_type;
	char					*redirection_file;
	struct s_redirections	*next;
}			t_redirections;

typedef struct s_arguments
{
	char				*arg;
	struct s_arguments	*next;
}				t_arguments;

typedef struct s_pipes
{
	char				*line;
	t_linedata			*sliced_line;
	char				*command;
	t_arguments			*arguments;
	t_redirections		*redirections;
	struct s_pipes		*next;
}				t_pipes;

typedef struct s_format
{
	char				*line;
	t_linedata			*sliced_line;
	char				*pre_pipe_line;
	char				*command;
	t_arguments			*arguments;
	t_redirections		*redirections;
	t_pipes				*pipes;
	int					pipe_presence;
	struct s_format		*next;
}				t_format;

typedef struct s_var_rep
{
	int		dollar_position;
	char	*variable_content;
	char	*variable_name;
}				t_var_rep;

typedef struct s_tools
{
	char	c;
	int		i;
	int		j;
	int		n;
	int		len;
	int		counter;
	char	*ret;
}				t_tools;

typedef struct s_toolbox
{
	t_format		*formaptr;
	t_history		*ptr;
	t_history		*tmp;
	int				ascii;
	char			*str;
	struct termios	old;
	int				i;
	char			*check;
}				t_toolbox;

typedef struct s_global
{
	int			stop;
	int			forked;
	int			p;
	int			ret;
	t_toolbox	*box;
}				t_global;

t_global	g_global;

char				*dollar_treatment(char	**env, char	*slice);
int					test_c(char	c);
ssize_t				find_valid_dollar(char	*slice);
char				*fetch_var_name(char	*slice, int	i);
char				*ft_strjoin_dollar_sign(char	*s1, char	*s2);
char				*var_replacement(t_var_rep	*data, char	*slice);
ssize_t				equal_sign(char	*str);
void				not_equ_m_one(t_env	*ptr, char	**env, int	i, int	equ);
void				equ_m_one(t_env	*ptr, char	**env, int	i);
t_env				*fetch_all_variables(char	**env);
char				*ft_strdup(char	*str);
char				*fetch_wanted_var(char	*name, t_env	*ptr);
char				*fetch_variable_content(t_env	*ptr, char	*name);
void				free_env_contens(t_env	*ptr);
void				free_env_nodes(t_env	*ptr);
void				dollar_freedom_1(t_var_rep	*data, t_env	*ptr_env);
void				var_freedom(t_var_rep	*data);
void				var_fetch(t_var_rep	*d, char	*s, int	i, t_env	*p);
void				set_glob(t_var_rep	*data);
char				*quotes_post_dollar(char	*slice, int	i);
char				*final_fetch(t_var_rep	*d, char	*s, int	i, t_env	*p);
int					quotes_err(char	*input, int	i);
int					da_loop(char	*input, int	i);
char				*error_check(char	*input);
int					tri(char	*input, int	i, char	**str);
int					parse_error_check(char	*input,	int	i);
int					redirection_error_check(char	*input, int i);
int					error_suite(int	counter, char	*input, int	i, char	*str);
ssize_t				ft_strlen(char	*string);
char				*my_calloc(int	length);
char				*my_realloc(char	*str, char	c);
int					my_strcmp(char	*s1, char	*s2);
char				*fetch_input(void);
void				*init_all(t_toolbox	*box);
void				put_strings(char	*a, char	*b, char	*c, char	*d);
void				init_history_node_data(t_toolbox	*box);
void				printable_key(t_toolbox	*box);
void				delete_key(t_toolbox	*box);
void				up_key(t_toolbox	*box);
void				down_key(t_toolbox	*box);
void				ctrl_d_key(t_toolbox	*box);
void				update_position(t_toolbox	*box);
void				*full_ws_niet(t_toolbox	*box, t_node	**head);
void				next_history_node(t_toolbox	*box);
void				*enter_key(t_toolbox	*box, t_node	**head);
t_toolbox			*parse_init(void);
void				initialise(t_bag	**b, t_linedata	**d, t_linedata	**t);
t_linedata			*split_id(char	*input);
char				*parse(t_toolbox	*box);
int					pipe_presence(char	*input);
char				*fetch_command(t_linedata	*data);
t_arguments			*f_16(t_arguments	*ptr, t_linedata	*data);
t_arguments			*fetch_arguments(t_linedata	*d, t_arguments	*r, int	c);
t_linedata			*a_s(t_linedata	*data, t_redirections	*ptr);
t_redirections		*fetch_reds(t_linedata	*d, t_redirections	*r, int	c);
t_pipes				*f2(t_format	*ptr, int	*start, int	i);
void				f3(t_format	*ptr, int	start, int	i);
int					skips(t_format	*ptr, int	i);
void				ft_end(t_format	*ptr, int	*i, int	start);
void				*fetch_pipes(t_format	*ptr, int	start, int	i);
void				assignments(t_format	*ptr);
void				*pipe_split(t_format	*ptr);
void				print_da(t_format	*ptr);//DONT NORM IT
void				purge(char	**env, t_format	*ptr);
void				cleanse_no_pipes(char	**env, t_format	*ptr);
void				cleanse_yes_pipes(char	**env, t_format	*ptr);
void				treat_slash(char	*slice, t_tools	*box);
void				treat_single_quote(char	*slice, t_tools	*box);
void				double_q_slash(char	*slice, t_tools	*box);
void				treat_double_quote(char	*slice, t_tools	*box);
char				*quote_slash(char	*slice);
int					skip_quotes(char	*input, int	i);
char				*trim_spaces(char	*input);
void				skip_un(char	*input, int	i, int	*a);
t_format			*fetch(t_format	*ptr, char	*input, int	*start, int	i);
void				*semicolon_split(t_format	*ptr, char	*input);
char				*last_check(t_toolbox	*box);
t_linedata			*pre_red(char	*input, t_bag	*bag, t_linedata	*data);
t_linedata			*red(char	*input, t_bag	*bag, t_linedata	*data);
void				ufo(t_linedata	*data);
t_linedata			*w_s(char	*input, t_bag	*bag, t_linedata	*data);
void				eof(char	*input, t_bag	*bag, t_linedata	*data);
t_linedata			*fetch_red(char	*input, t_bag	*bag, t_linedata	*data);
void				data_init(t_linedata	*data);
int					skip_irr(char	*input, int	i);
void				data_init0(t_bag	*data);
void				initialise_box(t_tools	*box, char	*slice);
char				*j_oin(char	*s, char	c);
int					fetch_char(struct termios	*old);
char				*ft_strdupe(char	*str);
int					put_char(int	c);
char				*delete_char(char	*str);
int					all_sp(char	*str);
int					ft_test_char(char	*str, char	c);
int					is_white_space(char	c);
int					back_slash_presence(char	*input, int	i);
char				*ft_substr(char	*str, int	start, int	end);
char				*ft_error(char	*str);
char				*ft_strjoin(char	*s1, char	*s2);
char				*ft_itoa(int	n);
void				free_history(void);
void				free_tformat(void);
void				yes_pipes_free(t_format	*tmp);
void				no_pipes_free(t_format	*ptr);
void				free_env_contens(t_env	*ptr);
void				free_env_nodes(t_env	*ptr);
void				free_sliced_contents(t_linedata	*ptr);
void				free_sliced_nodes(t_format	*ptr);
void				free_red_nodes(t_format	*ptr);
void				free_arg_nodes(t_format	*ptr);
void				free_arg_contents_yp(t_pipes	*ptr);
void				free_red_nodes_yp(t_pipes	*ptr);
void				free_arg_nodes_yp(t_pipes	*ptr);
void				free_sliced_nodes_yp(t_pipes	*ptr);
void				s1(t_pipes	*p, t_var_rep	*d,
						t_env	*e, t_arguments	*a);
void				s2(t_pipes	*p, t_var_rep	*d,
						t_env	*e, t_arguments	*a);
void				*o(t_format	*p, t_var_rep	*d,
						t_env	*pe, t_arguments	*ap);
void				s3(t_format	*p, t_var_rep	*d,
						t_env	*pe, t_arguments	*ap);
void				s4(t_format	*p, t_var_rep	*d,
						t_env	*pe, t_arguments	*ap);
void				free_contents(t_var_rep	*data);
void				fetch_contents(t_var_rep	*d, t_env	*p, t_pipes	*t);
void				last_free(t_var_rep	*data, t_env	*ptr_env);
void				*x_l(t_pipes	*ptr, t_var_rep	*d,
						t_env	*pe, t_arguments	*ap);
void				*x(t_pipes	*p, t_var_rep	*d,
						t_env	*pe, t_arguments	*ap);
void				*dollar_exception_yes_pipes(char	**env, t_format	*rtp);
void				treat_reda(t_redirections	*tmp_redirections, char **env);
void				purge_process(t_pipes	*tmp_pipes, char	**env);
void				redas(t_redirections	*tmp_redirections, char **env);
void				*dollar_exceptions_no_pipes(char	**env, t_format	*ptr);
void				free_contenta(t_var_rep	*data);
void				fetch_contenta(t_var_rep	*d, t_env	*p, t_format	*t);
void				last_freea(t_var_rep	*data, t_env	*ptr_env);
void				rep_dollar(char	*slice, int i);

#endif