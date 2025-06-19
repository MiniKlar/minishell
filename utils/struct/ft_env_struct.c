/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 04:30:54 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/19 03:37:38 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_convert_node_to_envp(t_envp *env)
{
	char *tmp;
	char *envp;
	char **final_envp;

	envp = NULL;
	if (!envp)
		envp = ft_strdup("");
	if (!envp)
		return (NULL);
	while (env)
	{
		tmp = envp;
		envp = ft_strjoin(envp, env->envp);
		free(tmp);
		tmp = envp;
		envp = ft_strjoin(envp, " ");
		free(tmp);
		env = env->next;
	}
	final_envp = ft_split(envp, ' ');
	free(envp);
	return(final_envp);
}

bool	find_change_env(t_envp *env, char *new_env, char *target_env)
{
	while (env)
	{
		if (ft_strncmp(env->envp, target_env, ft_strlen(target_env)) == 0)
		{
			free(env->envp);
			env->envp = ft_strdup(new_env);
			return (true);
		}
		env = env->next;
	}
	return (false);
}
