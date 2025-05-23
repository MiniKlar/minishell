/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:55:26 by lomont            #+#    #+#             */
/*   Updated: 2025/05/22 16:55:58 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_shell.h"

size_t	get_cmd_count(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
