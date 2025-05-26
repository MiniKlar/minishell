NAME 			= minishell

CC 				= cc
RM				= rm -f

CFLAGS 			= -Wall -Wextra -Werror -ggdb -I ./includes

LIB_SHELL			= LIB_SHELL

SRC 			= ./main.c \
				./parsing/token.c \
				./parsing/parsing.c \
				./utils/free.c \
				./built-ins/cd.c \
				./built-ins/env.c \
				./built-ins/pwd.c \
				./built-ins/exit.c \
				./built-ins/echo.c \
				./built-ins/unset.c \
				./built-ins/export.c \
				./utils/struct/ft_struct.c \
				./exec/exec.c  \
				./exec/infile.c \
				./exec/outfile.c \
				./exec/here_doc.c \
				./exec/exec_cmd.c  \
				./exec/pipex_utils.c \
				./exec/utils_path.c   \
				./exec/utils_exec.c	   \

OBJ 			= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./LIB_SHELL/LIB_SHELL.a -o $(NAME) -lreadline -ltermcap

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all bonus clean fclean re
