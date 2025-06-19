/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:34:38 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/18 00:30:32 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	progress_index_in_quote(char *line, int *i)
{
	size_t	index_matching_quote;

	index_matching_quote = find_corresponding_quote(line + *i, line[*i]);
	if (index_matching_quote == 0)
		return (false);
	if (index_matching_quote != 0)
	{
		while (index_matching_quote != 0)
		{
			*i += 1;
			index_matching_quote--;
		}
	}
	return (true);
}

static bool	is_quote(t_shell *shell, char *line, int *i, int *k)
{
	if (progress_index_in_quote(line, i) == false)
	{
		if (*k == 0)
			unexpected_quote(shell, find_next_quote(line + *i));
		else
			unexpected_quote(shell, find_next_quote(line + *k));
		return (false);
	}
	return (true);
}

static void	add_tokens_space(t_token **raw_tok, char *line, int *i, int *k)
{
	if (ft_isspace(line[*i - 1]) == false)
		add_token(raw_tok, line + *k, *i - *k, false);
	*k = *i + 1;
}

static bool	check_complete_line(t_shell *shell, t_token *raw_tok, char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (ft_isspace(line[i]) == true)
		i++;
	k = i;
	while (line[i])
	{
		if (ft_isspace(line[i]) == true)
			add_tokens_space(&raw_tok, line, &i, &k);
		else if (line[i] == '\'' || line[i] == '"')
		{
			if (is_quote(shell, line, &i, &k) == false)
				return (false);
		}
		i++;
	}
	if (ft_isspace(line[i - 1]) == false)
		add_token(&raw_tok, line + k, i, true);
	return (true);
}

t_token	*fill_raw_tokens(t_shell *shell, t_token **raw_tokens, char *line)
{
	*raw_tokens = init_token("");
	if (line[0] == '\0' || line[0] == ':' || line[0] == '!' || line[0] == '\t')
	{
		free((*raw_tokens)->value);
		free(*raw_tokens);
		return (NULL);
	}
	if (!check_complete_line(shell, *raw_tokens, line))
		return (*raw_tokens);
	return (*raw_tokens);
}
