NAME 			= parsing

CC 				= cc
RM				= rm -f

CFLAGS 			= -Wall -Wextra -Werror -ggdb -I ../includes -I ../LIB_SHELL

LIB_SHELL			= LIB_SHELL

SRC 			= token.c \
				parsing.c \
				lexer.c \
				parser.c \
				parsing_leo1.c \
				syntax.c \
				test_parsing.c \
				utils_parsing.c \


OBJ 			= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ../LIB_SHELL/lib_shell.a -o $(NAME) -lreadline -ltermcap

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

clear: fclean
	$(RM) -rf $(MLX)

re: fclean all

.PHONY:	all bonus clear clean fclean re
