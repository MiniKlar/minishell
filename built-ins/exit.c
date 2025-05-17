#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	free_shell(shell);
	rl_clear_history();
	exit(shell->wstatus); //doit exit sur le wstatus ou le exit code de lancienne commande
}
