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

void	free_child(t_shell *shell, char *command_path)
{
	if (command_path)
		free(command_path);
	free_array(shell->envp);
	free_all(shell);
	free(shell);
}

