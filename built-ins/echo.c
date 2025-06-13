#include "minishell.h"

// DANS CHILD

void	echo_w_arg(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->cmd[++i])
	{
		if (shell->cmd->cmd[i + 1] == NULL)
			ft_putstr_fd(shell->cmd->cmd[i], STDOUT_FILENO);
		else
		{
			ft_putstr_fd(shell->cmd->cmd[i], STDOUT_FILENO);
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
}

int	ft_echo(t_shell *shell)
{
	bool	has_arg;
	size_t	i;

	i = 0;
	has_arg = false;
	if (shell->cmd->cmd[1] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	else if (strncmp(shell->cmd->cmd[1], "-n", 3) == 0)
		has_arg = true;
	if (has_arg)
		echo_w_arg(shell);
	else
	{
		while (shell->cmd->cmd[++i])
		{
			ft_putstr_fd(shell->cmd->cmd[i], STDOUT_FILENO);
			if (shell->cmd->cmd[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (!has_arg)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
