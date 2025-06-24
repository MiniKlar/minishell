/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:49:05 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 19:15:41 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_arg_to_env(t_shell *shell, char *arg);

static void	replace_env(t_envp *previous_env, t_envp *new_envp)
{
	t_envp	*current_env;

	current_env = previous_env->next;
	new_envp->next = current_env->next;
	previous_env->next = new_envp;
	free(current_env->envp);
	free(current_env);
}

static bool	search_if_env_exist(t_envp *new_envp, t_envp **env)
{
	size_t	i;
	t_envp	*tmp;

	i = -1;
	while (new_envp->envp[++i])
	{
		if (new_envp->envp[i] == '=')
			break ;
	}
	while (*env)
	{
		if (ft_strncmp((*env)->envp, new_envp->envp, i) == 0)
		{
			replace_env(tmp, new_envp);
			return (true);
		}
		tmp = (*env);
		(*env) = (*env)->next;
	}
	return (false);
}

int	ft_export(t_shell *shell)
{
	size_t	i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (shell->cmd->cmd[i] == 0)
		export_all(shell->envp);
	if (shell->cmd->cmd[i])
	{
		if (ft_strncmp(shell->cmd->cmd[i], "-", 1) == 0
			&& ft_strlen(shell->cmd->cmd[i]) > 1)
		{
			error_export(shell->cmd->cmd[i], 1);
			return (1);
		}
	}
	while (shell->cmd->cmd[i])
	{
		if (check_arg_export_syntax(shell->cmd->cmd[i]) == true)
			export_arg_to_env(shell, shell->cmd->cmd[i]);
		else
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

static void	export_arg_to_env(t_shell *shell, char *arg)
{
	t_envp	*new_envp;
	t_envp	*env;
	t_envp	*tmp_env;
	char	**tmp;
	char	*new_arg;

	env = NULL;
	new_arg = remove_extra_char_before_egal(arg);
	new_envp = create_node_envp(new_arg);
	env = fill_envp(env, shell->envp);
	tmp_env = env;
	if (search_if_env_exist(new_envp, &env))
		env = tmp_env;
	else
	{
		env = tmp_env;
		ft_add_back_envp(&env, new_envp);
	}
	tmp = shell->envp;
	shell->envp = ft_convert_node_to_envp(env);
	free_array(tmp);
	free_env(env);
	free(new_arg);
}
