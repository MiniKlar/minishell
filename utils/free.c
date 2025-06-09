#include "minishell.h"

void	free_all(t_shell *shell)
{
	if (shell)
		free_shell(shell);
	if (shell->pipex && shell->is_child)
		free(shell->pipex);
	if (shell->id_fork && shell->is_child)
		free(shell->id_fork);
}

