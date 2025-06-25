/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:54:47 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 12:54:48 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*set_struct_pipex(t_shell *shell)
{
	t_pipe	*pipex;

	pipex = init_struct_pipex();
	if (!pipex)
	{
		printf("Error alloc pipex");
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
	return (pipex);
}

char	*find_command_exist_executable(t_shell *shell)
{
	char	*command_path;

	command_path = check_command_path(shell->cmd->cmd[0], shell->envp);
	if (command_path == NULL)
	{
		if (ft_strncmp(shell->cmd->cmd[0], "", 1) == 0)
			printf("bash:%s: command not found\n", shell->cmd->cmd[0]);
		else
			printf("bash: %s: command not found\n", shell->cmd->cmd[0]);
		free_child(shell, command_path);
		exit(127);
	}
	else
		return (command_path);
}

int	ft_wait(t_shell *shell, size_t nb_pipes, int *wstatus)
{
	size_t	i;

	i = 0;
	while (i != nb_pipes + 1)
	{
		if (waitpid(shell->id_fork[i], wstatus, 0) == -1)
		{
			perror("waitpid error");
			exit(1);
		}
		i++;
	}
	return (0);
}
