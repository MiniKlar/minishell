/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 04:29:00 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/25 01:46:27 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_free(t_shell *shell, int code)
{
	free_array(shell->envp);
	free_all(shell);
	free(shell->readline_cmd);
	free(shell);
	clear_history();
	exit(code);
}

void	print_error(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" not set\n", 2);
}

bool	check_has_options(char *arg, char *cmd)
{
	if (!arg)
		return (false);
	else
	{
		if (arg[0] == '-' && ft_strlen(arg) > 1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
			ft_putchar_fd(arg[0], 2);
			ft_putchar_fd(arg[1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			if (ft_strncmp(cmd, "pwd", 4) == 0)
			{
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": usage: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putchar_fd('\n', 2);
			}
			return (true);
		}
	}
	return (false);
}
