NAME 			= minishell

CC 				= cc
RM				= rm -f
CLONE 			= git clone --depth=1

CFLAGS 			= -Wall -Wextra -Werror -ggdb -I ./includes

LIB_C_GIT_URL 	= git@github.com:MiniKlar/LIB_C.git
LIB_C			= LIB_C

SRC 			= ./parsing/tokens_counter.c ./parsing/tokeniser.c \
				./parsing/parsing_leo/full_tokenization.c \
				./parsing/tokens_counter.c ./parsing_leo/tokenizer_suite/tokeniser.c \
				./parsing/parsing_leo/full_tokenization.c \
				./main.c \
				./parsing/token.c \
				./parsing/parsing_leo/tokenizer_suite.c \
				./utils/free.c ./utils/utils.c ./utils/utils.c \
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
