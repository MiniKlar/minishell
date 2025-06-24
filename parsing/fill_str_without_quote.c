/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_str_without_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 00:09:50 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 17:52:26 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_i_k(size_t *i, size_t *k)
{
	*i = 0;
	*k = 0;
}

static bool	check_quote_and_exp(char *line, char **str, size_t *i, size_t *k)
{
	if (line[*i] == '\'' || line[*i] == '"')
		return (false);
	else if (line[*i] == '$' && line[*i + 1] == '$')
	{
		*str = ft_join_str(*str, ft_strdup("$"));
		*i += 1;
		*k = *i;
	}
	return (true);
}

static char	*handle_normal_str(char *str, char *line, size_t *i, size_t *k)
{
	str = ft_join_str(str, ft_substr(line + *k, 0, 1));
	*i += 1;
	*k = *i;
	return (str);
}

static char	*is_expandable(char *line, char *str, size_t *i, int exit_code)
{
	char	*tmp_env;

	tmp_env = handle_env_variable(line + *i + 1, i, exit_code);
	if (!tmp_env)
		tmp_env = ft_strdup("");
	str = ft_join_str(str, tmp_env);
	return (str);
}

char	*fill_str_without_quote(char *line, size_t *index, int exit_code)
{
	size_t	i;
	size_t	k;
	char	*str;

	init_i_k(&i, &k);
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (line[i])
	{
		if (!check_quote_and_exp(line, &str, &i, &k))
			break ;
		else if (line[i] == '$' && line[i + 1] != '\0' && line[i + 1] != '$')
		{
			str = is_expandable(line, str, &i, exit_code);
			k = i;
		}
		else
			str = handle_normal_str(str, line, &i, &k);
	}
	*index += i;
	return (str);
}
