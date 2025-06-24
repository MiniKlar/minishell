/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:17 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 17:35:48 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	loop_env_variable(char *str, size_t *i)
{
	while (str[*i])
	{
		if (*i == 0 && ft_isdigit(str[*i]) == true)
		{
			*i = 1;
			break ;
		}
		else if (ft_isalnum(str[*i]) == 0)
			break ;
		else
			*i += 1;
	}
}

static char	*check_getenv(char *str)
{
	char	*env;

	env = NULL;
	if (!str)
		return (NULL);
	else
	{
		env = getenv(str);
		if (!env)
		{
			free(str);
			return (NULL);
		}
		else
		{
			free(str);
			return (ft_strdup(env));
		}
	}
}

char	*handle_env_variable(char *str, size_t *index_parsing, int exit_code)
{
	char	*env_variable;
	size_t	i;

	i = 0;
	if (str[0] == '?')
	{
		env_variable = ft_itoa(exit_code);
		i++;
	}
	else
	{
		loop_env_variable(str, &i);
		env_variable = check_getenv(ft_substr(str, 0, i));
	}
	if (index_parsing)
		*index_parsing += i + 1;
	if (!env_variable)
		return (NULL);
	return (env_variable);
}
