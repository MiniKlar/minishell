/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:48:42 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/19 03:18:05 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_arg(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	if (str[0] == '-' && str[1] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}

static void	check_if_arg(t_cmd *cmd, size_t *i, bool *has_arg)
{
	size_t	k;

	k = 1;
	*has_arg = false;
	while (cmd->cmd[k])
	{
		if (check_arg(cmd->cmd[k]))
			*has_arg = true;
		else if (!check_arg(cmd->cmd[k]) && *has_arg == false)
		{
			*i += 1;
			return ;
		}
		else if (!check_arg(cmd->cmd[k]) && *has_arg == true)
		{
			*i += k;
			return ;
		}
		k++;
	}
	if (*has_arg == true)
		*i = k;
	else
		*i = 1;
	return ;
}

static void	echo_w_arg(t_shell *shell, size_t *i)
{
	while (shell->cmd->cmd[*i])
	{
		if (shell->cmd->cmd[*i + 1] == NULL)
			ft_putstr_fd(shell->cmd->cmd[*i], STDOUT_FILENO);
		else
		{
			ft_putstr_fd(shell->cmd->cmd[*i], STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
		*i += 1;
	}
}

int	ft_echo(t_shell *shell)
{
	bool	has_arg;
	size_t	i;

	i = 0;
	if (shell->cmd->cmd[1] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	check_if_arg(shell->cmd, &i, &has_arg);
	if (has_arg)
		echo_w_arg(shell, &i);
	else
	{
		while (shell->cmd->cmd[i])
		{
			ft_putstr_fd(shell->cmd->cmd[i], STDOUT_FILENO);
			if (shell->cmd->cmd[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (!has_arg)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
