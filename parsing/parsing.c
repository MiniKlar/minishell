/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:34 by miniklar          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/06/23 18:30:44 by lpatin           ###   ########.fr       */
=======
/*   Updated: 2025/06/25 00:47:01 by lpatin           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

<<<<<<< Updated upstream
=======
void	error_heredoc_creation(t_shell **shell)
{
	(*shell)->cmd = (*shell)->first_cmd;
	free_shell((*shell));
	shell = NULL;
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
				return (false);
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

>>>>>>> Stashed changes
t_shell	*parse_tokens(t_shell *shell, t_token *tokens)
{
	shell->cmd = init_cmd(NULL);
	if (!shell->cmd)
	{
		ft_putstr_fd("Error memory allocation shell->cmd", 2);
		exit(EXIT_FAILURE);
	}
	process_token(&shell, tokens);
	return (shell);
}

t_token	*proccess_raw_tokens(t_token *raw_tokens, int exit_code)
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
	tokens = proccess_raw_tokens(raw_tokens, shell->exit_code);
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
	shell->first_cmd = shell->cmd;
	free_token_struct(tokens);
	return (true);
}
