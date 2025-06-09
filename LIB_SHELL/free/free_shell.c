/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:06 by lomont            #+#    #+#             */
/*   Updated: 2025/06/07 01:00:18 by miniklar         ###   ########.fr       */
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
	if (shell->fd_in > 0)
		close(shell->fd_in);
	if (shell->fd_out > 1)
		close(shell->fd_out);
	if (shell->tmp_stdin > 0)
		close(shell->tmp_stdin);
	if (shell->tmp_stdout > 0)
		close(shell->tmp_stdout);
}
