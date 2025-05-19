#include "minishell.h"

//DANS CHILD

void	ft_env(t_shell *shell)
{
	if (!shell->envp)
		perror("env");
	else
		print_tab(shell->envp);
	return ;
}
