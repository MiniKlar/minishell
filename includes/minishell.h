#ifndef MINISHELL_H
# define MINISHELL_H

#include "../LIB_C/LIB_C.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include </usr/include/stdio.h>
#include </usr/include/readline/readline.h>
#include </usr/include/readline/history.h>

typedef enum s_quote
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote;

typedef struct	s_token
{
	char			*value;
	struct s_token	*next;
	t_quote		quote_type;
	size_t 		nb_tokens;
}	t_token;

typedef enum s_symbol
{
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
}	t_symbol;

typedef struct s_redir
{
	t_symbol		symbol;
	char			*str;
	struct s_redir	*next;
}	t_redir;

typedef struct s_shell
{
	char			**cmd;
	t_redir			*redir;
	size_t			nb_pipe;
	int				wstatus;
	int				hdc_idx;
	struct s_shell	*next;
}	t_shell;


void	free_tab(char **tab);
void	ft_strtok(t_token *tokens, char *str);
int		ft_nb_tokens(char *str);

#endif
