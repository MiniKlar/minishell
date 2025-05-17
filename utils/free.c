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
	if (shell == NULL)
		return ;
	else
	{
		//free_tab(shell->cmd->cmd);
		free(shell->cmd);
		if (shell->redir != NULL)
			free_redir_struct(shell->redir);
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
