/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:49:05 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/19 00:48:51 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_arg_export_syntax(char *arg);
static char	*remove_extra_char_before_egal(char *arg);
static bool	error_export(char *arg, int error_code);
static void	export_all(char **envp);
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
			break;
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
		if (ft_strncmp(shell->cmd->cmd[i], "-", 1) == 0 &&
			ft_strlen(shell->cmd->cmd[i]) > 1)
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

static char	*remove_char_arg(char *arg)
{
	char	*new_arg;
	size_t	i;

	i = 0;
	new_arg = malloc(sizeof(char) * (ft_strlen(arg)));
	if (!new_arg)
		return (NULL);
	while (arg[i] != '=')
		i++;
	ft_memmove(new_arg, arg, i - 1);
	ft_memmove(new_arg + i - 1, arg + i, ft_strlen(arg) - i);
	new_arg[ft_strlen(arg) - 1] = '\0';
	return (new_arg);
}

static char	*remove_extra_char_before_egal(char *arg)
{
	size_t	i;
	bool	remove_char;

	i = 0;
	remove_char = false;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] == '=' && (arg[i] == '+'
			|| arg[i] == '_' || arg[i] == '<' || arg[i] == '>'))
			remove_char = true;
		i++;
	}
	if (remove_char == true)
		return (remove_char_arg(arg));
	return (ft_strdup(arg));
}

static bool	check_arg_export_syntax(char *arg)
{
	size_t	i;
	bool	egal_seen;

	i = 0;
	egal_seen = false;
	if ((!ft_isalpha(arg[0]) && arg[0] != '_') || arg[0] == '\0')
		return (error_export(arg, 0));
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			egal_seen = true;
			break ;
		}
		else if (ft_isalnum(arg[i]) != true && arg[i + 1] != '=' && arg[i] != '_')
			return (error_export(arg, 0));
		else if (ft_isalnum(arg[i]) != true && arg[i + 1] == '=' && arg[i] != '+'
					&& arg[i] != '_' && arg[i] != '<' && arg[i] != '>')
			return (error_export(arg, 0));
	}
	if (egal_seen)
		return (true);
	return (false);
}

static bool	error_export(char *arg, int error_code)
{
	if (error_code == 1)
	{
		ft_putstr_fd("bash: export: ", 2);
		ft_putchar_fd(arg[0], 2);
		ft_putchar_fd(arg[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	else
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (false);
}

static void	export_all(char **envp)
{
	size_t	i;
	size_t	k;
	size_t	index_egal;

	i = 0;
	while (envp[i])
	{
		k = -1;
		index_egal = 0;
		ft_putstr_fd("export ", 1);
		while (envp[i][++k])
		{
			if (k > 0)
				if (envp[i][k - 1] == '=')
					ft_putchar_fd('"', 1);
			if (envp[i][k] == '=')
				index_egal = k;
			ft_putchar_fd(envp[i][k], 1);
		}
		if (envp[i][k] == '\0' && index_egal != k - 1)
			ft_putstr_fd("\"\n", 1);
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
}
