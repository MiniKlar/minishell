/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:18:53 by lomont            #+#    #+#             */
/*   Updated: 2025/06/12 00:05:02 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	free_cmd_struct(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			free_array(cmd->cmd);
		if (cmd->redir != NULL)
		{
			free_redir_struct(cmd->redir);
			//printf("tu rentres ici pour free struct\n");
		}
		free(cmd);
		cmd = tmp;
	}
}
