/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:05:03 by lomont            #+#    #+#             */
/*   Updated: 2025/06/24 20:21:41 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_id_fork_number(t_shell *shell, size_t *i)
{
	if (shell->id_fork[*i] == -1)
	{
		printf("Error fork id_fork[%zu]", *i);
		ft_exit(shell);
	}
	if (shell->id_fork[*i] == 0)
	{
		set_signals_default();
		create_child(shell);
	}
	if (shell->id_fork[*i] != 0)
	{
		if (shell->nb_pipe > 0)
			pipe_struct_update(shell, *i);
		shell->cmd = shell->cmd->next;
		*i += 1;
	}
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
		check_id_fork_number(shell, &i);
	}
	if (shell->pipex)
	{
		if (shell->pipex->in_fd != -1)
			close(shell->pipex->in_fd);
	}
	shell->cmd = tmp;
	set_signals_interactive();
}
