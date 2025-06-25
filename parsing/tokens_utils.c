/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:43:00 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 01:24:54 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	forward_tokens(t_token **tokens, int *index, int *i)
{
	while (*index != *i)
	{
		if ((*tokens) != NULL)
			(*tokens) = (*tokens)->next;
		*index += 1;
	}
}

void	next_tokens(t_token **tokens, int i)
{
	int	index;

	index = 0;
	if (!tokens)
		return ;
	if (i == 1)
		*tokens = (*tokens)->next;
	else if (i == 2)
		forward_tokens(tokens, &index, &i);
	else
	{
		while (*tokens)
		{
			if (is_redirection((*tokens)) > 0
				|| ft_strncmp((*tokens)->value, "|", 2) == 0)
				break ;
			else
				*tokens = (*tokens)->next;
		}
	}
}

bool	check_redir_delimiter(char *str, int *idx_str)
{
	size_t	index;

	index = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		index = 2;
	else if (str[0] == '>' || str[0] == '<' || str[0] == '|')
		index = 1;
	if (index == 0)
		return (false);
	*idx_str += index;
	return (true);
}
