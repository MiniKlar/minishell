#include "minishell.h"

t_pipe	*init_struct_pipex(void)
{
	t_pipe	*pipex;

	pipex = malloc(sizeof(*pipex));
	if (!pipex)
		return (NULL);
	pipex->pipe_index = FIRST_PIPE;
	pipex->in_fd = -1;
	return (pipex);
}

void	pipe_struct_update(t_shell *shell, size_t i)
{
	if (i != shell->nb_pipe - 1)
		shell->pipex->pipe_index = N_PIPE;
	else
		shell->pipex->pipe_index = LAST_PIPE;
	if (shell->pipex->in_fd != -1)
	{
		close(shell->pipex->in_fd);
		shell->pipex->in_fd = -1;
	}
	shell->pipex->in_fd = dup(shell->pipex->fdpipe[0]);
	close(shell->pipex->fdpipe[0]);
	close(shell->pipex->fdpipe[1]);
}
