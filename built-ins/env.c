/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:48:58 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/19 01:40:43 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_first_arg_cmd(t_shell *shell)
{
	size_t	i;
	int		size_cmd;
	char	**tmp;
	char	**cmd;

	i = 1;
	while (shell->cmd->cmd[i])
		i++;
	size_cmd = i;
	cmd = malloc(sizeof(char *) * size_cmd);
	cmd[size_cmd - 1] = NULL;
	i = 1;
	while(shell->cmd->cmd[i])
	{
		cmd[i - 1] = ft_strdup(shell->cmd->cmd[i]);
		i++;
	}
	tmp = shell->cmd->cmd;
	shell->cmd->cmd = cmd;
	free_array(tmp);
}

static bool	check_arg_is_command(t_shell *shell)
{
	size_t	i;
	char	*cmd_path;

	i = 1;
	while(shell->cmd->cmd[i])
	{
		if (ft_strncmp(shell->cmd->cmd[i], "env", 4) != 0)
		{
			del_first_arg_cmd(shell);
			cmd_path = check_command_path(shell->cmd->cmd[0], shell->envp);
			if (!cmd_path)
			{
				ft_putstr_fd("env: ", 2);
				ft_putstr_fd(shell->cmd->cmd[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				shell->exit_code = 127;
			}
			else
			{
				if (ft_strncmp(cmd_path, shell->cmd->cmd[0], ft_strlen(cmd_path)) == 0)
					free(cmd_path);
				exec(shell);
			}
			return (false);
		}
		i++;
	}
	return (true);
}

int	ft_env(t_shell *shell)
{
	if (shell->cmd->cmd[1])
	{
		if (!check_arg_is_command(shell))
			return (shell->exit_code);
	}
	if (!shell->envp)
	{
		perror("env");
		return (1);
	}
	else
		print_array(shell->envp);
	return (0);
}
