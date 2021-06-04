NAME = minishell

SRC =	main.c \
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_exec.c \
		builtins/ft_exit.c \
		builtins/ft_export.c \
		builtins/ft_path.c \
		builtins/ft_pwd.c \
		builtins/ft_setpipes.c \
		builtins/ft_strcmp.c \
		builtins/ft_unset.c \
		builtins/redirections.c \
		builtins/tools.c \
		builtins/tools2.c \
		builtins/tools3.c \
		builtins/tools4.c \
		builtins/tools5.c \
		builtins/tools6.c \
		builtins/tools7.c \
		builtins/tools8.c \
		parse/dollar_1.c \
		parse/dollar_2.c \
		parse/dollar_3.c \
		parse/dollar_4.c \
		parse/dollar_treatment.c \
		parse/error_check.c \
		parse/error_check_1.c \
		parse/fetch_input.c \
		parse/freedom_file.c \
		parse/ft_itoa.c \
		parse/functions_headerfile.h \
		parse/no_pipes.c \
		parse/no_pipes_1.c \
		parse/parse.c \
		parse/pipes.c \
		parse/pipes_1.c \
		parse/pipes_2.c \
		parse/print.c \
		parse/purge.c \
		parse/purge_1.c \
		parse/purge_1_suite.c \
		parse/purge_1_suite1.c \
		parse/purge_2.c \
		parse/purge_2_suite.c \
		parse/quotes_backslash.c \
		parse/semi_split.c \
		parse/semi_split_1.c \
		parse/supp1.c \
		parse/supp2.c \
		parse/supp_1_v1.c \
		parse/term.c \
		parse/term_0.c \
		parse/term_1.c \
		parse/term_1_v1.c \
		parse/term_1_v2.c \
		parse/utils.c \
		parse/utils_1.c \
		parse/yes_pipes.c \
		parse/yes_pipes_1.c \
		
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C ./libft
	gcc -ltermcap $(SRC) $(FLAGS) ./libft/libft.a
	mv a.out minishell

clean:
	@make re -C ./libft

fclean: clean
	rm -rf ./minishell
	@make fclean -C ./libft

re: fclean all