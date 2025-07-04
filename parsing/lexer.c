/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:20 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 19:21:53 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	in_quote(char c, char *current_quote)
{
	if (*current_quote == 0 && (c == '\'' || c == '"'))
	{
		*current_quote = c;
		return (true);
	}
	else if (c == *current_quote)
	{
		*current_quote = 0;
		return (true);
	}
	return (*current_quote != 0);
}

void	add_token(t_token **tokens, char *str, size_t i, bool full_str)
{
	char	*tmp;

	if (!full_str)
	{
		tmp = ft_substr(str, 0, i);
		token_add_back(tokens, token_new(ft_strdup(tmp)));
		free(tmp);
	}
	else
		token_add_back(tokens, token_new(ft_strdup(str)));
}

int	last_case(t_token **tokens, char *line, size_t i)
{
	add_token(tokens, &line[i], 1, false);
	return (i + 1);
}

int	handle_metacharacter(t_token **tokens, char *line, size_t i)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_token(tokens, &line[i], 2, false);
		return (i + 1);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		add_token(tokens, &line[i], 2, false);
		return (i + 1);
	}
	else if (line[i] == '>' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
	{
		add_token(tokens, &line[i], 1, false);
		return (i + 1);
	}
	else if (line[i] == '<' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
	{
		add_token(tokens, &line[i], 1, false);
		return (i + 1);
	}
	else if (line[i] == '|' && line[i + 1] == ' ')
		last_case(tokens, line, i);
	return (i);
}
