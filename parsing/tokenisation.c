/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:41 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/17 03:29:15 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*tokenisation(t_shell *shell, char *line)
{
	t_token	*raw_tokens;

	raw_tokens = fill_raw_tokens(shell, &raw_tokens, line);
	if (!raw_tokens)
		return (NULL);
	ft_del_first_raw_tokens(&raw_tokens);
	return (raw_tokens);
}

char	*handle_quote(char *str_to_parse, int exit_code)
{
	size_t	i;
	char	*line;
	char	*str;
	char	quote;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	i = 0;
	while (str_to_parse[i])
	{
		str = NULL;
		quote = str_to_parse[i];
		if (quote == '\'' || quote == '"')
			str = fill_str_with_quote(str_to_parse + i, &i, exit_code);
		else
			str = fill_str_without_quote(str_to_parse + i, &i, exit_code);
		line = ft_join_str(line, str);
	}
	return (line);
}
