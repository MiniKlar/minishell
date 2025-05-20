#include "minishell.h"

void	free_redir_struct(t_redir *redirections);
void	free_struct_pipe(t_pipe *pipex);
void	free_shell(t_shell *shell);

void	free_all(t_shell *shell, t_pipe *pipex)
{
	free_shell(shell);
	if (pipex)
		free_struct_pipe(pipex);
	exit(EXIT_FAILURE);
}

void	free_shell(t_shell *shell)
{
	t_cmd *tmp;

	if (shell == NULL)
		return ;
	else
	{
		if (shell->cmd->redir == NULL)
			;
		else
			free_redir_struct(shell->cmd->redir);
		while (shell->cmd->next != NULL)
		{
			free_tab(shell->cmd->cmd);
			tmp = shell->cmd->next;
			free(shell->cmd);
			shell->cmd = tmp;
		}
	}
}

void	free_struct_pipe(t_pipe *pipex)
{
	if (pipex->fdpipe != NULL)
		free(pipex->fdpipe);
	free(pipex);
}

void free_redir_struct(t_redir *redirections)
{
	t_redir	*tmp;

	while (redirections != NULL)
	{
		tmp = redirections;
		free(redirections->str);
		redirections = redirections->next;
		free(tmp);
	}
}
