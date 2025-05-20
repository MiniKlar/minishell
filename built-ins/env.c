#include "minishell.h"

//DANS CHILD

int	ft_env(t_shell *shell)
{
	if (!shell->envp)
	{
		perror("env");
		return (1);
	}
	else
		print_tab(shell->envp);
	return (0);
}
