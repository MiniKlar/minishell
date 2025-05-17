#include "minishell.h"

// DANS CHILD

void	echo_w_arg(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->cmd[++i])
	{
		if (shell->cmd->cmd[i + 1] == NULL)
			printf("%s",shell->cmd->cmd[i]);
		else
			printf("%s ",shell->cmd->cmd[i]);
	}
}

void	ft_echo(t_shell *shell)
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
		echo_w_arg(shell);
	else
	{
		while (shell->cmd->cmd[++i])
			printf("%s ",shell->cmd->cmd[i]);
	}
	if (!has_arg)
		printf("\n");
}
