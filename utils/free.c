#include "minishell.h"

void	free_all(t_shell *shell, t_pipe *pipex)
{
	free_shell(shell);
	if (pipex)
		free(pipex);
}

