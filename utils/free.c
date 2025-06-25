#include "minishell.h"

void	free_eof(t_shell *shell)
{
	free_array(shell->envp);
	free(shell);
	write(STDOUT_FILENO, "exit\n", 5);
}

void	free_all(t_shell *shell)
{
	if (shell->pipex && shell->is_child)
		free(shell->pipex);
	if (shell->id_fork && shell->is_child)
		free(shell->id_fork);
	if (shell)
		free_shell(shell);
}

void	free_child(t_shell *shell, char *command_path)
{
	free_array(shell->envp);
	free_all(shell);
	if (command_path)
		free(command_path);
	free(shell);
}
