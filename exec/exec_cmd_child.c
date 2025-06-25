/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:14:42 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/25 12:39:20 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redir(t_shell *shell, char *command_path)
{
	bool	error;

	error = false;
	if (!redir_cmd_input_output(shell, &error))
	{
		if (shell->is_child)
		{
			free_child(shell, command_path);
			exit(EXIT_FAILURE);
		}
	}
}

static void	execution_builtins_in_child(t_shell *shell, char *command_path)
{
	exec_built_in(shell, true);
	free_child(shell, command_path);
	exit(EXIT_SUCCESS);
}

static void	execution_command_in_child(t_shell *shell, char *command_path)
{
	if (execve(command_path, &shell->cmd->cmd[0], shell->envp) == -1)
	{
		perror("Error execve");
		free_child(shell, command_path);
		exit(126);
	}
}

void	create_child(t_shell *shell)
{
	char	*command_path;
	bool	is_built_ins;

	command_path = NULL;
	is_built_ins = is_cmd_built_ins(shell);
	check_redir(shell, command_path);
	if (!is_built_ins && shell->cmd->cmd)
		command_path = find_command_exist_executable(shell);
	if (shell->pipex)
	{
		if (shell->pipex->pipe_index != FIRST_PIPE)
			ft_dup(shell, command_path);
	}
	ft_dup_redir(shell, true);
	if (shell->nb_pipe > 0 && shell->pipex->pipe_index == FIRST_PIPE)
		ft_dup(shell, command_path);
	if (is_built_ins)
		execution_builtins_in_child(shell, command_path);
	if (shell->cmd->cmd)
		execution_command_in_child(shell, command_path);
	free_child(shell, command_path);
	exit(EXIT_SUCCESS);
}
