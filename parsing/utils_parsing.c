/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:43 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/25 10:01:56 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_metacharacter(char *str)
{
	if (str[0] == '|')
		return (true);
	else if (str[0] == '<' || str[0] == '>')
		return (true);
	else if (ft_strlen(str) > 1)
	{
		if ((str[0] == '<' || str[1] == '<')
			&& (str[0] == '>' || str[1] == '>'))
			return (true);
	}
	return (false);
}

char	find_next_quote(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			break ;
		else
			i++;
	}
	return (line[i]);
}

char	*ft_join_str(char *line, char *to_append)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(line, to_append);
	free(tmp);
	free(to_append);
	return (line);
}

t_token	*token_new(char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	else if (ft_strncmp(token->value, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(token->value, ">", 2) == 0)
		return (2);
	else if (ft_strncmp(token->value, "<<", 3) == 0)
		return (3);
	else if (ft_strncmp(token->value, ">>", 3) == 0)
		return (4);
	else if (ft_strncmp(token->value, "<>", 3) == 0)
		return (5);
	else
		return (0);
}
