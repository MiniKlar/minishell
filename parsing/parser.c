/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:28 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/25 00:32:52 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_pipe_to_shell(t_shell *shell, t_cmd *cmd)
{
	cmd_add_back(&shell->cmd, cmd);
	shell->nb_pipe++;
}

int	handle_redirection_token(t_token *tokens, t_cmd *cmd)
{
	handle_redirection(tokens, cmd);
	return (0);
}

size_t	find_corresponding_quote(char *line, char quote_to_find)
{
	size_t	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == quote_to_find)
			return (i);
		else
			i++;
	}
	return (0);
}
