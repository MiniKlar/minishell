#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	int exit_code;

	exit_code = shell->wstatus;
	ft_putstr_fd("exit\n", 1);
	free_array(shell->envp);
	free_all(shell);
	free(shell);
	clear_history();
	exit(exit_code);
}
