/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:35 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:30:15 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

char	*get_env_value(char *name, char **envp)
{
	int			i;
	size_t		len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

char	*extract_env_name(char *var)
{
	char	*env_name;
	size_t	len;

	if (!var)
		return (NULL);
	if (var[0] == '$')
		env_name = var + 1;
	else
		env_name = var;
	len = ft_strlen(env_name);
	if (len >= 2 && env_name[0] == '"' && env_name[len - 1] == '"')
		return (ft_substr(env_name, 1, len - 2));
	if (len >= 2 && env_name[0] == '\'' && env_name[len - 1] == '\'')
		return (NULL);
	return (ft_strdup(env_name));
}
