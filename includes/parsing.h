#pragma once

# include "minishell.h"

bool	parsing(t_shell *shell, char *line);

/* Lexer */
t_token	*tokenisation(t_shell *shell, char *line);
t_token	*token_new(char *value);
void	add_token(t_token **tokens, char *str, size_t i, bool full_str);
size_t	find_corresponding_quote(char *line, char quote_to_find);

/* Parser */
t_shell	*parse_tokens(t_shell *shell, t_token *tokens);
char	*check_getenv(char *str);
char	*check_env_variable(char *str, char quote, int exit_code);
char	*handle_env_variable(char *str, size_t *index_parsing, int exit_code);

/* Syntax */
bool	check_syntax(t_shell *shell, t_token *tokens);
t_token	*proccess_raw_tokens(t_token *raw_tokens, int exit_code);

/* Utils */
bool	is_metacharacter(char *c);
int		is_redirection(t_token *token);
int		handle_redirection(t_token *current, t_cmd *cmd);
void	handle_syntax_error(t_shell *shell, t_token **tokens, char c);
int		handle_metacharacter(t_token **tokens, char *line, size_t i);
int		handle_redirection_token(t_token *tokens, t_cmd *cmd);
int		handle_regular_token(t_shell *shell, t_token **tokens, char *line, bool *in_quote);
int		handle_pipe_token(t_cmd **current_cmd, char ***args, int *arg_count);
void	ft_del_first_raw_tokens(t_token **tokens);
/* Error */
int		syntax_error(char *msg);
int		unexpected_quote(t_shell *shell, t_token *tokens, char quote);
