/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redir_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:18:38 by lomont            #+#    #+#             */
/*   Updated: 2025/06/06 22:42:30 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

void	free_redir_struct(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	while (redir)
	{
		tmp = redir->next;
		free(redir->str);
		free(redir);
		redir = tmp;
	}
}
