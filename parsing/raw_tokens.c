/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:34:38 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/25 00:34:20 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_tokens_space(t_token **raw_tok, char *line, int *i, int *k)
{
	add_token(raw_tok, line + *k, *i - *k, false);
	*i += 1;
	*k = *i;
}

static int	ft_skip_isspace(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

static bool	check_isspace_metachar(t_token *tok, char *line, int *i, int *k)
{
	if (ft_isspace(line[*i]))
	{
		add_tokens_space(&tok, line, i, k);
		*i += ft_skip_isspace(line + *i);
		*k = *i;
		return (true);
	}
	else if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
	{
		check_redir_delimiter(line + *k, i);
		add_token(&tok, line + *k, *i - *k, false);
		*i += ft_skip_isspace(line + *i);
		*k = *i;
		return (true);
	}
	return (false);
}

static bool	check_complete_line(t_shell *shell, t_token *raw_tok, char *line)
{
	int	i;
	int	k;

	i = ft_skip_isspace(line);
	if (line[i] == '\0')
		return (false);
	k = i;
	while (line[i])
	{
		if (check_isspace_metachar(raw_tok, line, &i, &k))
			;
		else if (line[i] == '\'' || line[i] == '"')
		{
			while (line[i] == '\'' || line[i] == '"')
			{
				if (!is_quote(shell, line, &i, &k))
					return (false);
			}
		}
		else
			i++;
	}
	if (k != i)
		add_token(&raw_tok, line + k, i - k, false);
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
	{
		free_token_struct((*raw_tokens));
		return (NULL);
	}
	return (*raw_tokens);
}
