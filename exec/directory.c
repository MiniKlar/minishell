/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:20:42 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 01:24:25 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_directory(t_shell *shell)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(shell->cmd->cmd[0], 2);
	ft_putstr_fd(": filename argument required ", 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(shell->cmd->cmd[0], 2);
	ft_putstr_fd(": usage: . filename [arguments]\n", 2);
	shell->exit_code = 2;
}

static bool	is_directory(char *str, DIR *dir)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			break ;
	}
	if (str[i] == '\0')
		return (false);
	dir = opendir(str);
	if (dir != NULL)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is directory\n", 2);
		closedir(dir);
	}
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (true);
}

bool	check_if_directory(t_shell *shell)
{
	struct stat	filestat;

	if (!shell->cmd->cmd[0])
		return (false);
	if (shell->cmd->cmd[0][0] == '.' && shell->cmd->cmd[0][1] == '\0')
		return (print_error_directory(shell), true);
	else
	{
		if (access(shell->cmd->cmd[0], F_OK) != -1)
		{
			if (stat(shell->cmd->cmd[0], &filestat) == -1)
			{
				perror("stat");
				return (NULL);
			}
			if ((filestat.st_mode & S_IFMT) == S_IFDIR)
			{
				is_directory(shell->cmd->cmd[0], NULL);
				shell->exit_code = 126;
				return (true);
			}
		}
	}
	return (false);
}
