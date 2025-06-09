/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 04:28:29 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/06 04:28:49 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	free_env(t_envp *env)
{
	t_envp	*tmp;

	if (!env)
		return ;
	else
	{
		while (env != NULL)
		{
			tmp = env;
			free(env->envp);
			env = env->next;
			free(tmp);
		}
	}
}
