#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	int exit_code;

	exit_code = shell->wstatus;
	ft_putstr_fd("exit\n", 1);
	free_array(shell->envp);
	free_shell(shell);
	free(shell);
	rl_clear_history();
	exit(exit_code);
}
