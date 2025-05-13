NAME 			= minishell

CC 				= cc
RM				= rm -f
CLONE 			= git clone --depth=1

CFLAGS 			= -Wall -Wextra -Werror -ggdb -I ./includes

LIB_C_GIT_URL 	= git@github.com:MiniKlar/LIB_C.git
LIB_C			= LIB_C

SRC 			= ./parsing/parsing.c \
				./parsing/token.c \
				./utils/free.c \
				./built-ins/cd.c \
				./built-ins/pwd.c \
				./built-ins/exit.c \
				./built-ins/echo.c \
				./built-ins/export.c \
				./built-ins/env.c \
				./main.c \
				./utils/struct/ft_add.c \
				./utils/struct/ft_get.c \
				./utils/struct/ft_struct.c \
				./exec/pipe.c \
				./exec/utils.c \
				./exec/exec.c \
				./exec/redirections.c \
				./exec/pipex_utils.c \
				./exec/infile.c \
				./exec/outfile.c \
				./exec/here_doc.c \

OBJ 			= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIB_C) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./LIB_C/LIB_C.a -o $(NAME) -lreadline -ltermcap

$(LIB_C):
	git clone $(LIB_C_GIT_URL) $(LIB_C)
	$(MAKE) -C $(LIB_C)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(LIB_C)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

clear: fclean
	$(RM) -rf $(MLX)

re: fclean all

.PHONY:	all bonus clear clean fclean re
