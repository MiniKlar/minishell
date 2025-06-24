/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:14:08 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/24 20:19:16 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_first_pipe(t_shell *shell)
{
	if (shell->cmd->fd_out == -1)
	{
		if (dup2(shell->pipex->fdpipe[1], STDOUT_FILENO) == -1)
		{
			printf("Error dup2 --> FIRST_PIPE\n");
			return (-1);
		}
	}
	return (0);
}

static int	dup_n_pipe(t_shell *shell)
{
	if (shell->cmd->fd_in == -1)
	{
		if (dup2(shell->pipex->in_fd, STDIN_FILENO) == -1)
		{
			printf("Error dup2 --> N_PIPE STDIN\n");
			return (-1);
		}
	}
	if (shell->cmd->fd_out == -1)
	{
		if (dup2(shell->pipex->fdpipe[1], STDOUT_FILENO) == -1)
		{
			printf("Error dup2 --> N_PIPE STDOUT\n");
			return (-1);
		}
	}
	return (0);
}

static int	dup_last_pipe(t_shell *shell)
{
	if (shell->cmd->fd_in == -1)
	{
		if (dup2(shell->pipex->in_fd, STDIN_FILENO) == -1)
		{
			printf("Error dup2 --> LAST_PIPE STDIN\n");
			return (-1);
		}
	}
	return (0);
}

int	dup_pipe(t_shell *shell)
{
	int	p;

	p = shell->pipex->pipe_index;
	if (p == FIRST_PIPE)
	{
		if (dup_first_pipe(shell) == -1)
			return (-1);
	}
	else if (p == N_PIPE)
	{
		if (dup_n_pipe(shell) == -1)
			return (-1);
	}
	else if (p == LAST_PIPE)
	{
		if (dup_last_pipe(shell) == -1)
			return (-1);
	}
	return (0);
}
