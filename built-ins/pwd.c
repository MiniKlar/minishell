/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:49:07 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/18 03:52:58 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, bool print)
{
	char	*buffer;

	if (check_has_options(shell->cmd->cmd[1], "pwd"))
		return (1);
	buffer = malloc(sizeof(char) * 1024);
	if (getcwd(buffer, 1024) == NULL)
		perror("pwd error");
	else
	{
		if (print)
			printf("%s\n", buffer);
	}
	free(buffer);
	return (0);
}
