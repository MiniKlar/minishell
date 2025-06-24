/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:12:32 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/24 17:15:15 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_std_back(t_shell *shell)
{
	dup2(shell->tmp_stdin, STDIN_FILENO);
	dup2(shell->tmp_stdout, STDOUT_FILENO);
	close(shell->tmp_stdin);
	close(shell->tmp_stdout);
	shell->tmp_stdin = -1;
	shell->tmp_stdout = -1;
}

void	ft_dup_std(t_shell *shell)
{
	shell->tmp_stdin = dup(STDIN_FILENO);
	shell->tmp_stdout = dup(STDOUT_FILENO);
}

void	ft_dup(t_shell *shell, char *command_path)
{
	if (dup_pipe(shell) == -1)
	{
		printf("error dup_pipe\n");
		free_array(shell->envp);
		free_all(shell);
		free(shell);
		if (command_path)
			free(command_path);
		exit(1);
	}
	if (shell->pipex->in_fd != -1)
	{
		close(shell->pipex->in_fd);
		shell->pipex->in_fd = -1;
	}
	close(shell->pipex->fdpipe[0]);
	close(shell->pipex->fdpipe[1]);
}

void	ft_dup_redir(t_shell *shell, bool is_child)
{
	if (shell->cmd->fd_in > -1)
	{
		dup2(shell->cmd->fd_in, STDIN_FILENO);
		close(shell->cmd->fd_in);
		shell->cmd->fd_in = -1;
	}
	if (shell->cmd->fd_out > -1)
	{
		dup2(shell->cmd->fd_out, STDOUT_FILENO);
		close(shell->cmd->fd_out);
		shell->cmd->fd_out = -1;
	}
	if (shell->tmp_stdin > -1 && is_child == true)
	{
		close(shell->tmp_stdin);
		shell->tmp_stdin = -1;
	}
	if (shell->tmp_stdout > -1 && is_child == true)
	{
		close(shell->tmp_stdout);
		shell->tmp_stdout = -1;
	}
}
