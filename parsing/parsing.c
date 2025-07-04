/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:34 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/25 09:50:19 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	error_heredoc_creation(t_shell **shell)
{
	(*shell)->cmd = (*shell)->first_cmd;
	free_shell((*shell));
	return ;
}

t_shell	*process_heredoc(t_shell **shell)
{
	int		i;
	t_redir	*tmp_redir;

	i = 0;
	(*shell)->first_cmd = (*shell)->cmd;
	while ((*shell)->cmd)
	{
		tmp_redir = (*shell)->cmd->redir;
		while ((*shell)->cmd->redir)
		{
			if ((*shell)->cmd->redir->symbol != HERE_DOC)
				;
			else if (!here_doc((*shell)->cmd, i))
			{
				error_heredoc_creation(shell);
				return (NULL);
			}
			(*shell)->cmd->redir = (*shell)->cmd->redir->next;
			i++;
		}
		(*shell)->cmd->redir = tmp_redir;
		(*shell)->cmd = (*shell)->cmd->next;
	}
	(*shell)->cmd = (*shell)->first_cmd;
	return (*shell);
}

t_shell	*parse_tokens(t_shell *shell, t_token *tokens)
{
	shell->cmd = init_cmd(NULL);
	if (!shell->cmd)
	{
		ft_putstr_fd("Error memory allocation shell->cmd", 2);
		exit(EXIT_FAILURE);
	}
	process_token(&shell, tokens);
	if (process_heredoc(&shell) == NULL)
		shell = NULL;
	return (shell);
}

t_token	*process_raw_tokens(t_token *raw_tokens, int exit_code)
{
	t_token	*tokens;
	char	*str;

	tokens = init_token("");
	while (raw_tokens)
	{
		str = handle_quote(raw_tokens->value, exit_code);
		free(raw_tokens->value);
		raw_tokens->value = str;
		if (str)
			add_token(&tokens, str, 0, true);
		raw_tokens = raw_tokens->next;
	}
	ft_del_first_raw_tokens(&tokens);
	return (tokens);
}

bool	parsing(t_shell *shell, char *line)
{
	t_token	*raw_tokens;
	t_token	*tokens;

	raw_tokens = tokenisation(shell, line);
	if (!raw_tokens)
		return (false);
	tokens = process_raw_tokens(raw_tokens, shell->exit_code);
	free_token_struct(raw_tokens);
	if (!tokens)
		return (false);
	if (!check_syntax(shell, tokens))
	{
		free_token_struct(tokens);
		return (false);
	}
	shell = parse_tokens(shell, tokens);
	if (!shell)
	{
		free_token_struct(tokens);
		free_shell(shell);
		return (false);
	}
	free_token_struct(tokens);
	return (true);
}
