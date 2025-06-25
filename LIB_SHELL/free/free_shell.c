/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:06 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 11:57:16 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	shell->nb_pipe = 0;
	shell->is_child = false;
	if (shell->cmd->fd_in > -1)
		close(shell->cmd->fd_in);
	if (shell->cmd->fd_out > -1)
		close(shell->cmd->fd_out);
	if (shell->tmp_stdin > -1)
		close(shell->tmp_stdin);
	if (shell->tmp_stdout > -1)
		close(shell->tmp_stdout);
	if (shell->cmd)
		free_cmd_struct(shell->first_cmd);
}
