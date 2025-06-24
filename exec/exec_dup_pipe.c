/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:14:08 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/24 17:25:42 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_pipe(t_shell *shell)
{
	int	p;

	p = shell->pipex->pipe_index;
	if (p == FIRST_PIPE)
	{
		if (shell->cmd->fd_out == -1)
		{
			if (dup2(shell->pipex->fdpipe[1], STDOUT_FILENO) == -1)
			{
				printf("Error dup2 --> FIRST_PIPE\n");
				return (-1);
			}
		}
	}
	else if (p == N_PIPE)
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
	}
	else if (p == LAST_PIPE)
	{
		if (shell->cmd->fd_in == -1)
		{
			if (dup2(shell->pipex->in_fd, STDIN_FILENO) == -1)
			{
				printf("Error dup2 --> LAST_PIPE STDIN\n");
				return (-1);
			}
		}
	}
	return (0);
}
