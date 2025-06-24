/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 23:37:28 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 23:59:16 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	redir_in_case(t_shell *shell, t_redir *tmp_redir, bool *error)
{
	if (!redir_infile(shell))
	{
		shell->cmd->redir = tmp_redir;
		*error = true;
		return (false);
	}
	return (true);
}

bool	redir_out_case(t_shell *shell, t_redir *tmp_redir, bool *error)
{
	if (!redir_outfile(shell))
	{
		shell->cmd->redir = tmp_redir;
		*error = true;
		return (false);
	}
	return (true);
}

bool	redir_heredoc_case(t_shell *shell, char *heredoc_n, bool *error)
{
	heredoc_n = shell->cmd->redir->str;
	if (heredoc_n)
	{
		if (!ft_tmp_open_heredoc(shell->cmd))
		{
			*error = true;
			return (false);
		}
		unlink(heredoc_n);
	}
	return (true);
}

bool	redir_cmd_input_output(t_shell *shell, bool *error)
{
	char		*heredoc_name;
	t_symbol	type_redir;
	t_redir		*tmp_redir;

	heredoc_name = NULL;
	if (!shell->cmd->redir)
		return (true);
	else
		tmp_redir = shell->cmd->redir;
	while (shell->cmd->redir != NULL)
	{
		type_redir = shell->cmd->redir->symbol;
		if (type_redir == REDIR_IN)
			redir_in_case(shell, tmp_redir, error);
		else if (type_redir == REDIR_OUT || type_redir == APPEND)
			redir_out_case(shell, tmp_redir, error);
		else if (type_redir == HERE_DOC)
			redir_heredoc_case(shell, heredoc_name, error);
		if (*error == true)
			return (shell->cmd->redir = tmp_redir, false);
		shell->cmd->redir = shell->cmd->redir->next;
	}
	shell->cmd->redir = tmp_redir;
	return (true);
}
