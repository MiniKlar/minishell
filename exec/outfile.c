/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:55:04 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 12:55:05 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redir_outfile(t_shell *shell)
{
	int		fd;
	char	*str;

	str = shell->cmd->redir->str;
	if (shell->cmd->redir->symbol == APPEND)
		fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0755);
	else
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (false);
	}
	if (shell->cmd->fd_out > -1)
		close(shell->cmd->fd_out);
	shell->cmd->fd_out = fd;
	return (true);
}
