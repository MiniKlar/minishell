#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/include/libft.h"

typedef enum s_symbol
{
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND
}	t_symbol;

typedef struct s_redir
{
	t_symbol		symbol;
	char			*str;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char			**envp;
	t_cmd			*cmd;
	size_t			nb_pipe;
	int				fd_in;
	int				fd_out;
	int				wstatus;
	int				hdc_idx;
}	t_shell;

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

int		parsing(char *line, t_shell *shell);

/* Lexer */
t_token	*lexer(char *line);
t_token	*token_new(char *value);
void	token_add_back(t_token **tokens, t_token *new);

/* Parser */
int		parse_tokens(t_token *tokens, t_shell *shell);

/* Syntax */
int		check_syntax(t_token *tokens);

/* Utils */
void	free_tokens(t_token *tokens);
void	free_shell(t_shell *shell);
int		is_metacharacter(char c);
int		is_redirection(t_token *token);
int		handle_redirection(t_token **current, t_redir **redir);
int		ft_strcmp(const char *s1, const char *s2);

/* Error */
int		syntax_error(const char *msg);

#endif
