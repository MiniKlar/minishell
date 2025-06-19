/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:49:10 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/19 01:16:24 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_if_in_envp(char **envp, char *str)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	ft_unset(t_shell *shell)
{
	char	**tmp;
	char	*name_to_unset;
	t_envp	*env;
	size_t	i;

	i = 0;
	while (shell->cmd->cmd[++i] != 0)
	{
		tmp = NULL;
		env = NULL;
		name_to_unset = shell->cmd->cmd[i];
		if (check_if_in_envp(shell->envp, name_to_unset) == true)
		{
			env = fill_envp(env, shell->envp);
			ft_delone_env(env, shell->cmd->cmd[i]);
			tmp = shell->envp;
			shell->envp = ft_convert_node_to_envp(env);
			free_array(tmp);
			free_env(env);
		}
	}
	return (0);
}
