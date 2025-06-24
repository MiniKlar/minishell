/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:16:52 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/24 17:26:35 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	built_ins_1(t_shell *shell);

bool	built_ins_2(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd[0], "pwd", 4) == 0)
		shell->exit_code = ft_pwd(shell, true);
	else if ((ft_strncmp(shell->cmd->cmd[0], "echo", 5) == 0))
		shell->exit_code = ft_echo(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "env", 4) == 0)
		shell->exit_code = ft_env(shell);
	else
		return (false);
	return (true);
}

bool	built_ins_1(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
		return (false);
	if (ft_strncmp(shell->cmd->cmd[0], "export", 5) == 0)
		shell->exit_code = ft_export(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "cd", 3) == 0)
		shell->exit_code = ft_cd(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "unset", 6) == 0)
		shell->exit_code = ft_unset(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "exit", 5) == 0)
		ft_exit(shell);
	else if (built_ins_2(shell) == false)
		return (false);
	return (true);
}

bool	is_cmd_built_ins(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
		return (false);
	else if (ft_strncmp(shell->cmd->cmd[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "cd", 3) == 0)
		return (true);
	else if ((ft_strncmp(shell->cmd->cmd[0], "echo", 5) == 0))
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "env", 4) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "unset", 6) == 0)
		return (true);
	return (false);
}
