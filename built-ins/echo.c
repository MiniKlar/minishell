#include "minishell.h"

void	echo_cmd(t_shell *shell);

int ft_echo(t_shell *shell)
{
	pid_t id_fork;
	id_fork = fork();
	if (id_fork == -1)
		perror("fork");
	if (id_fork == 0)
		echo_cmd(shell);
	waitpid(id_fork, &shell->wstatus, 0);
	return (0);
}

void	echo_cmd(t_shell *shell)
{
	bool	has_arg;
	size_t	i;

	i = 0;
	has_arg = false;
	if (shell->cmd->cmd[1] == NULL)
	{
		printf("\n");
		return ;
	}
	else if (strncmp(shell->cmd->cmd[1], "-n", 3) == 0)
		has_arg = true;
	if (has_arg)
	{
		i = 1;
		while (shell->cmd->cmd[++i])
		{
			if (shell->cmd->cmd[i + 1] == NULL)
				printf("%s",shell->cmd->cmd[i]);
			else
				printf("%s ",shell->cmd->cmd[i]);
		}
	}
	else
	{
		while (shell->cmd->cmd[++i])
			printf("%s ",shell->cmd->cmd[i]);
	}
	if (!has_arg)
		printf("\n");
}
