/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:48:49 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/19 03:38:16 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_if_too_many_args(t_shell *shell)
{
	if (shell->cmd->cmd[1])
	{
		if (shell->cmd->cmd[2])
		{
			ft_putstr_fd("bash: cd: too many arguments\n", 2);
			return (true);
		}
	}
	return (false);
}

static void	update_pwd(t_shell *shell)
{
	t_envp	*env;
	char	*new_pwd;
	char	*new_env;

	env = NULL;
	env = fill_envp(env, shell->envp);
	new_pwd = getcwd(NULL, 0);
	new_env = ft_strjoin("OLDPWD=", getenv("PWD"));
	if (!find_change_env(env, new_env, "OLDPWD="))
		ft_add_back_envp(&env, create_node_envp(new_env));
	free(new_env);
	new_env = ft_strjoin("PWD=", new_pwd);
	find_change_env(env, new_env, "PWD=");
	free(new_env);
	free_array(shell->envp);
	shell->envp = ft_convert_node_to_envp(env);
	free_env(env);
	free(new_pwd);
}

static int	exec_cd(t_shell *shell, char *arg)
{
	if (chdir(arg) == -1)
	{
		perror("cd");
		free(arg);
		return (1);
	}
	else
	{
		free(arg);
		update_pwd(shell);
		return (0);
	}
}

static char	*handle_specific_case(char *directory)
{
	char		*arg;

	arg = NULL;
	if (ft_strncmp(directory, "~", 2) == 0)
	{
		arg = getenv("HOME");
		if (!arg)
			arg = gethome_without_env();
		else
			arg = ft_strdup(arg);
	}
	else if (ft_strncmp(directory, "-", 2) == 0)
	{
		arg = ft_strdup(getenv("OLDPWD"));
		if (!arg)
			print_error("OLDPWD");
	}
	else
		arg = ft_strdup(directory);
	return (arg);
}

int	ft_cd(t_shell *shell)
{
	char	*arg;
	char	*directory;

	if (check_if_too_many_args(shell))
		return (1);
	if (check_has_options(shell->cmd->cmd[1], "cd"))
		return (1);
	directory = shell->cmd->cmd[1];
	if (directory == NULL)
	{
		arg = getenv("HOME");
		if (arg)
			arg = ft_strdup(arg);
		else
			print_error("HOME");
	}
	else
		arg = handle_specific_case(directory);
	if (arg != NULL)
		return (exec_cd(shell, arg));
	else
		return (1);
}
