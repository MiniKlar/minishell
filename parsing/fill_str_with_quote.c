/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_str_with_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 00:07:07 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/18 22:31:41 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*is_expandable(char *line, char *str, int exit_code, size_t *i)
{
	char	*tmp_env;

	if (ft_isalnum(line[*i + 1]) == 0 && line[*i + 1] != '?')
	{
		tmp_env = ft_strdup("$");
		*i += 1;
	}
	else
		tmp_env = handle_env_variable(line + *i + 1, i, exit_code);
	if (!tmp_env)
		tmp_env = ft_strdup("\0");
	str = ft_join_str(str, tmp_env);
	return (str);
}

static char	*is_closing_quote(char *line, char *str, size_t *i, size_t *k)
{
	if (str)
	{
		str = ft_join_str(str, ft_substr(line + *k, 0, *i - *k));
		return (str);
	}
	else
		return (ft_substr(line + *k, 0, *i - *k));
}

char	*fill_str_with_quote(char *line, size_t *index, int exit_code)
{
	size_t	i;
	size_t	k;
	char	*str;

	i = 1;
	k = i;
	str = ft_strdup("");
	if (!str)
		return (NULL);
	if (line[0] == line[i])
		return (*index += i + 1, str);
	while (line[i])
	{
		if (line[i] == line[0])
			return (*index += i + 1, is_closing_quote(line, str, &i, &k));
		else if (line[i] == '$' && line[0] == '"')
			str = is_expandable(line, str, exit_code, &i);
		else
		{
			str = ft_join_str(str, ft_substr(line + i, 0, 1));
			i++;
		}
		k = i;
	}
	return (NULL);
}
