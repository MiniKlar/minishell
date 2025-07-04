/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:20:57 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/25 11:58:52 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_no_command(t_shell *shell)
{
	shell->is_child = false;
	if (shell->cmd->redir)
	{
		check_redir(shell, NULL);
		ft_dup_std(shell);
		ft_dup_redir(shell, false);
		ft_dup_std_back(shell);
	}
}

bool	exec_built_in(t_shell *shell, bool is_child)
{
	if (!is_child)
		shell->is_child = false;
	else
		shell->is_child = true;
	if (!is_cmd_built_ins(shell) && is_child == false)
		return (false);
	check_redir(shell, NULL);
	if (!is_child)
	{
		ft_dup_std(shell);
		ft_dup_redir(shell, false);
	}
	built_ins_1(shell);
	if (!is_child)
		ft_dup_std_back(shell);
	return (true);
}

void	exec(t_shell *shell)
{
	if ((!shell->cmd->cmd[0] && shell->nb_pipe == 0)
		|| check_if_directory(shell))
		return (exec_no_command(shell));
	else if (shell->nb_pipe == 0 && exec_built_in(shell, false) == true)
		return ;
	else
	{
		shell->is_child = true;
		exec_cmd(shell);
	}
}
