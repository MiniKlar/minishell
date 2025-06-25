/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:54:41 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 12:54:42 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_command_path(char *command, char **envp)
{
	char	**path_tab;
	char	*new_command;
	char	*path;

	if (!command || !envp[0] || ft_strncmp(command, "Makefile", 9) == 0)
		return (NULL);
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	if (ft_strchr(command, '/') != NULL && access(command, F_OK | X_OK) != 0)
		return (NULL);
	path = recup_env(envp);
	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	new_command = ft_strjoin("/", command);
	free(path);
	return (new_command_function(path_tab, new_command));
}

char	*recup_env(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strtrim(envp[i], "PATH="));
		else
			path = NULL;
		i++;
	}
	return (path);
}

char	*new_command_function(char **path, char *new_command)
{
	int		i;
	char	*command_path;

	i = 0;
	while (path[i])
	{
		command_path = ft_strjoin(path[i], new_command);
		if (access(command_path, F_OK) == 0)
		{
			free_array(path);
			free(new_command);
			return (command_path);
		}
		else
			free(command_path);
		i++;
	}
	free_array(path);
	free(new_command);
	return (NULL);
}
