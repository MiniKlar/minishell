/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:57:40 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 12:57:41 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "minishell.h"

bool	parsing(t_shell *shell, char *line);
t_token	*tokenisation(t_shell *shell, char *line);
t_token	*token_new(char *value);
void	add_token(t_token **tokens, char *str, size_t i, bool full_str);
void	next_tokens(t_token **tokens, int i);

/* Parser */

t_shell	*parse_tokens(t_shell *shell, t_token *tokens);
char	*handle_env_variable(char *str, size_t *index_parsing, int exit_code);
int		process_token(t_shell **shell, t_token *tokens);
char	*handle_quote(char *str_to_parse, int exit_code);
char	find_next_quote(char *line);
char	*fill_str_with_quote(char *line, size_t *index, int exit_code);
char	*fill_str_without_quote(char *line, size_t *index, int exit_code);
bool	is_quote(t_shell *shell, char *line, int *i, int *k);
bool	check_redir_delimiter(char *str, int *idx_str);

/* Syntax */

bool	check_syntax(t_shell *shell, t_token *tokens);
t_token	*process_raw_tokens(t_token *raw_tokens, int exit_code);
t_token	*fill_raw_tokens(t_shell *shell, t_token **raw_tokens, char *line);

/* Utils */

bool	is_metacharacter(char *c);
int		is_redirection(t_token *token);
int		handle_redirection(t_token *current, t_cmd *cmd);
int		handle_metacharacter(t_token **tokens, char *line, size_t i);
int		handle_redirection_token(t_token *tokens, t_cmd *cmd);
void	ft_del_first_raw_tokens(t_token **tokens);
char	*ft_join_str(char *line, char *to_append);

/* Error */

bool	unexpected_token(t_shell *shell, char *token);
int		unexpected_quote(t_shell *shell, char quote);
void	handle_syntax_error(t_shell *shell, t_token **tokens, char c);

//REDIRECTIONS

bool	redir_outfile(t_shell *shell);
bool	redir_infile(t_shell *shell);
bool	redir_cmd_input_output(t_shell *shell, bool *error);
bool	here_doc(t_cmd *cmd, int i);
bool	heredoc_wrapper(t_cmd *cmd, int fd);
