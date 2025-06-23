/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:36 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/23 18:30:25 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	check_pipe_syntax(t_shell *shell, t_token *tokens)
{
	size_t	i;

	i = 0;
	while (tokens->value[i])
	{
		if (tokens->value[i] == '|' && tokens->value[i + 1] == '|')
			return (unexpected_token(shell, "||"));
		if (tokens->value[i] == '|' && is_metacharacter(tokens->value + 1))
		{
			unexpected_token(shell, "|");
			return (false);
		}
		if (i > 0)
		{
			if (tokens->value[i] == '|' && is_metacharacter(tokens->value
					+ (i - 1)))
			{
				unexpected_token(shell, "|");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool	check_redirection(t_shell *shell, t_token *tokens)
{
	size_t	i;
	size_t	k;
	char	*str;

	i = 0;
	k = 0;
	while (tokens->value[i])
	{
		if (is_metacharacter(tokens->value + i))
			k++;
		if (k == 3)
		{
			i = i - k + 1;
			str = ft_substr(tokens->value + i, 0, 2);
			unexpected_token(shell, str);
			free(str);
			return (false);
		}
		if (!is_metacharacter(tokens->value + i))
			k = 0;
		i++;
	}
	return (true);
}

static bool	check_metacharacter(t_shell *shell, t_token *tokens)
{
	if (is_redirection(tokens) != 0)
	{
		if (is_metacharacter(tokens->value) && !tokens->next)
			return (unexpected_token(shell, NULL));
		else if (is_metacharacter(tokens->next->value))
			return (unexpected_token(shell, tokens->next->value));
	}
	if (!check_redirection(shell, tokens))
		return (false);
	return (true);
}

bool	check_syntax(t_shell *shell, t_token *tokens)
{
	if (!tokens)
		return (false);
	if (tokens->value[0] == '|' && tokens->value[1] == '\0')
		return (unexpected_token(shell, tokens->value));
	while (tokens)
	{
		if (!check_metacharacter(shell, tokens))
			return (false);
		if (!check_pipe_syntax(shell, tokens))
			return (false);
		if (tokens->value[0] == '&' && tokens->value[1] == '&')
			return (unexpected_token(shell, "&&"));
		if (tokens->value[0] == '|' && ((tokens->value[1] != '\0')
				|| !tokens->next))
			return (unexpected_token(shell, "|"));
		if (tokens->value[0] == '<' && tokens->value[1] == '>'
			&& tokens->value[2] == '\0')
			return (unexpected_token(shell, NULL));
		tokens = tokens->next;
	}
	return (true);
}
