#pragma once

# include "minishell.h"

int		parsing(t_shell *shell, char *line);

/* Lexer */
t_token	*tokenisation(t_shell *shell, char *line);
t_token	*token_new(char *value);
void	add_token(t_token **tokens, char *str, size_t i);

/* Parser */
int		parse_tokens(t_shell *shell, t_token *tokens);

/* Syntax */
int		check_syntax(t_shell *shell, t_token *tokens);

/* Utils */
bool	is_metacharacter(char *c);
int		is_redirection(t_token *token);
int		handle_redirection(t_token *current, t_cmd *cmd);
void	handle_syntax_error(t_shell *shell, t_token **tokens, char c);
int		handle_metacharacter(t_token **tokens, char *line, size_t i);
int		handle_redirection_token(t_token *tokens, t_cmd *cmd);
int		handle_regular_token(t_shell *shell, t_token **tokens, char *line, bool *in_quote);
int		handle_pipe_token(t_cmd **current_cmd, char ***args, int *arg_count);
/* Error */
int		syntax_error(char *msg);
int		unexpected_quote(t_shell *shell, t_token *tokens, char *str);
