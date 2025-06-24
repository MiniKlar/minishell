/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:28 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/25 00:01:55 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	find_corresponding_quote(char *line, char quote_to_find)
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

static bool	progress_index_in_quote(char *line, int *i)
{
	size_t	index_matching_quote;

	index_matching_quote = find_corresponding_quote(line + *i, line[*i]);
	if (index_matching_quote == 0)
		return (false);
	else if (index_matching_quote == 1)
		*i += 2;
	else if (index_matching_quote != 0)
	{
		while (index_matching_quote != 0)
		{
			*i += 1;
			index_matching_quote--;
		}
		*i += 1;
	}
	return (true);
}

bool	is_quote(t_shell *shell, char *line, int *i, int *k)
{
	if (!progress_index_in_quote(line, i))
	{
		if (*k == 0)
			unexpected_quote(shell, find_next_quote(line + *i));
		else
			unexpected_quote(shell, find_next_quote(line + *k));
		return (false);
	}
	return (true);
}

int	handle_redirection_token(t_token *tokens, t_cmd *cmd)
{
	handle_redirection(tokens, cmd);
	return (0);
}
