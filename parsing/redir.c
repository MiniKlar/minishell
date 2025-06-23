/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 23:37:28 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/23 02:40:00 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	redir_cmd_input_output(t_shell *shell)
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
		{
			if (!redir_infile(shell))
			{
				shell->cmd->redir = tmp_redir;
				return (false);
			}
		}
		else if (type_redir == REDIR_OUT || type_redir == APPEND)
		{
			if (!redir_outfile(shell))
			{
				shell->cmd->redir = tmp_redir;
				return (false);
			}
		}
		else if (type_redir == HERE_DOC)
		{
			heredoc_name = shell->cmd->redir->str;
			if (heredoc_name)
			{
				if (!ft_tmp_open_heredoc(shell->cmd))
					return (false);
				unlink(heredoc_name);
				free(heredoc_name);
			}
		}
		shell->cmd->redir = shell->cmd->redir->next;
	}
	shell->cmd->redir = tmp_redir;
	return (true);
}
