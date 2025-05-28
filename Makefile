NAME 			= minishell

CC 				= cc
RM				= rm -f

CFLAGS 			= -Wall -Wextra -Werror -ggdb -I ./includes

LIB_SHELL		= LIB_SHELL

SRC 			= ./main.c \
				./built-ins/cd.c \
				./built-ins/env.c \
				./built-ins/pwd.c \
				./built-ins/exit.c \
				./built-ins/echo.c \
				./built-ins/unset.c \
				./built-ins/export.c \
				./exec/exec.c  \
				./exec/infile.c \
				./exec/outfile.c \
				./exec/here_doc.c \
				./exec/exec_cmd.c  \
				./exec/pipex_utils.c \
				./exec/utils_path.c   \
				./exec/utils_exec.c	   \
				./parsing/token.c \
				./parsing/parsing.c \
				./parsing/lexer.c \
				./parsing/parser.c \
				./parsing/parsing_leo1.c \
				./parsing/syntax.c \
				./parsing/utils_parsing.c \
				./utils/free.c \
				./utils/struct/ft_struct.c \

OBJ 			= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./LIB_SHELL/lib_shell.a -o $(NAME) -lreadline -ltermcap

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all bonus clean fclean re
