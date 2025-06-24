/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:49:02 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/24 19:53:11 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_exit(t_shell *shell, char *cmd, int error, int *code)
{
	if (error == 0)
	{
		if (cmd)
		{
			ft_putstr_fd("bash: exit", 2);
			ft_putstr_fd(": too many arguments\n", 2);
			shell->exit_code = 1;
		}
	}
	else if (error == 1)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*code = 255;
		exit_status_free(shell, *code);
	}
}

static void	check_over_or_underflow(long long val, t_shell *shell, int *code)
{
	char	*str;
	char	sign;

	str = shell->cmd->cmd[1];
	sign = '\0';
	if (ft_isdigit(str[0]) == true || str[0] == '+')
		sign = '+';
	else if (str[0] == '-')
		sign = '-';
	if ((sign == '+' && val < 0) || (sign == '-' && val > 0))
		print_error_exit(shell, shell->cmd->cmd[1], 1, code);
}

static int	ft_size_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array || !array[0])
		return (0);
	while (array[i])
		i++;
	return (i);
}

static void	check_if_number(char *cmd, int *is_number)
{
	size_t	i;

	i = 0;
	*is_number = 0;
	if (cmd)
	{
		while (cmd[i] != '\0')
		{
			if (i == 0)
			{
				if (cmd[i] == '+' || cmd[i] == '-')
					i++;
			}
			if (ft_isdigit(cmd[i]) == 1)
				*is_number = 1;
			else
			{
				*is_number = 2;
				break ;
			}
			i++;
		}
	}
}

void	ft_exit(t_shell *shell)
{
	int			code;
	int			exit_code;
	int			is_number;
	long long	val;

	ft_putstr_fd("exit\n", 1);
	if (ft_size_array(shell->cmd->cmd) > 2)
	{
		print_error_exit(shell, shell->cmd->cmd[1], 0, &code);
		return ;
	}
	if (!shell->cmd->cmd[1])
		exit_status_free(shell, shell->exit_code);
	check_if_number(shell->cmd->cmd[1], &is_number);
	if (is_number == 1)
	{
		val = ft_atoll(shell->cmd->cmd[1]);
		check_over_or_underflow(val, shell, &code);
		exit_code = (int)(val);
		code = exit_code & 0xFF;
	}
	if (is_number == 2)
		print_error_exit(shell, shell->cmd->cmd[1], 1, &code);
	exit_status_free(shell, code);
}
