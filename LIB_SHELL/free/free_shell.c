/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:06 by lomont            #+#    #+#             */
<<<<<<< Updated upstream
<<<<<<< Updated upstream
/*   Updated: 2025/06/19 02:29:51 by miniklar         ###   ########.fr       */
=======
/*   Updated: 2025/06/25 02:09:52 by lpatin           ###   ########.fr       */
>>>>>>> Stashed changes
=======
/*   Updated: 2025/06/25 02:09:52 by lpatin           ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmd)
		free_cmd_struct(shell->first_cmd);
	shell->nb_pipe = 0;
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	if (shell->fd_in > -1)
		close(shell->fd_in);
	if (shell->fd_out > -1)
		close(shell->fd_out);
	if (shell->tmp_stdin > -1)
		close(shell->tmp_stdin);
	if (shell->tmp_stdout > -1)
		close(shell->tmp_stdout);
=======
=======
>>>>>>> Stashed changes
	if (shell->cmd)
	{
		if (shell->cmd->fd_in > -1)
			close(shell->cmd->fd_in);
		if (shell->cmd->fd_out > -1)
			close(shell->cmd->fd_out);
		free_cmd_struct(shell->first_cmd);
	}
		if (shell->tmp_stdin > -1)
			close(shell->tmp_stdin);
		if (shell->tmp_stdout > -1)
			close(shell->tmp_stdout);
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}
