NAME 			= minishell

CC 				= cc
RM				= rm -f

CFLAGS 			= -Wall -Wextra -Werror -ggdb -I ./includes

LIB_SHELL		= LIB_SHELL

MAKE			= make

SRC 			= ./main.c \
				./built-ins/cd.c \
				./built-ins/env.c \
				./built-ins/pwd.c \
				./built-ins/exit.c \
				./built-ins/echo.c \
				./built-ins/unset.c \
				./built-ins/export.c \
				./built-ins/export_utils.c \
				./exec/exec_builtins.c \
				./exec/exec_cmd_child.c \
				./exec/exec_cmd_utils.c \
				./exec/exec_dup_pipe.c \
				./exec/exec.c  \
				./exec/infile.c \
				./exec/outfile.c \
				./exec/exec_cmd.c  \
				./exec/pipex_utils.c \
				./exec/utils_path.c   \
				./exec/utils_exec.c	   \
				./parsing/raw_tokens.c \
				./parsing/fill_str_with_quote.c \
				./parsing/fill_str_without_quote.c \
				./parsing/expansion.c   \
				./parsing/tokens.c \
				./parsing/parsing.c \
				./parsing/lexer.c \
				./parsing/parser.c \
				./parsing/tokenisation.c \
				./parsing/syntax.c \
				./parsing/here_doc.c \
				./parsing/redir.c \
				./parsing/redirs_utils.c \
				./parsing/utils_parsing.c \
				./parsing/error_message.c \
				./utils/free.c \
				./utils/struct/ft_struct.c \
				./utils/struct/ft_env_struct.c \
				./utils/built-ins/built-ins_utils.c \
				./utils/built-ins/cd_utils.c \
				./utils/signal.c \
				./utils/signals_bis.c \

OBJ 			= $(SRC:.c=.o)

all: $(NAME)
$(LIB_SHELL):
	$(MAKE) -C LIB_SHELL all

$(NAME): $(LIB_SHELL) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./LIB_SHELL/lib_shell.a -o $(NAME) -lreadline -ltermcap

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C LIB_SHELL clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C LIB_SHELL fclean

re: fclean all

.PHONY:	all clean fclean re LIB_SHELL
