/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:14:42 by lpatin            #+#    #+#             */
/*   Updated: 2025/06/24 19:17:04 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_child(t_shell *shell)
{
	char	*command_path;
	bool	is_built_ins;

	command_path = NULL;
	is_built_ins = is_cmd_built_ins(shell);
	if (!redir_cmd_input_output(shell))
	{
		free_child(shell, command_path);
		exit(EXIT_FAILURE);
	}
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
	{
		exec_built_in(shell, true);
		free_child(shell, command_path);
		exit(EXIT_SUCCESS);
	}
	if (shell->cmd->cmd)
	{
		if (execve(command_path, &shell->cmd->cmd[0], shell->envp) == -1)
		{
			perror("Error execve");
			free_child(shell, command_path);
			exit(126);
		}
	}
	free_child(shell, command_path);
	exit(EXIT_SUCCESS);
}

void	create_children(t_shell *shell)
{
	size_t	i;
	t_cmd	*tmp;

	i = 0;
	set_signals_exec();
	tmp = shell->cmd;
	while (shell->cmd != NULL)
	{
		create_fdpipe(shell);
		shell->id_fork[i] = fork();
		if (shell->id_fork[i] == -1)
		{
			printf("Error fork id_fork[%zu]", i);
			ft_exit(shell);
		}
		if (shell->id_fork[i] == 0)
		{
			set_signals_default();
			create_child(shell);
		}
		if (shell->id_fork[i] != 0)
		{
			if (shell->nb_pipe > 0)
				pipe_struct_update(shell, i);
			shell->cmd = shell->cmd->next;
			i++;
		}
	}
	if (shell->pipex)
	{
		if (shell->pipex->in_fd != -1)
			close(shell->pipex->in_fd);
	}
	shell->cmd = tmp;
	set_signals_interactive();
}
