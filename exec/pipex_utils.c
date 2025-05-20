#include "minishell.h"

t_pipe	*init_struct_pipex(void)
{
	t_pipe	*pipex;

	pipex = malloc(sizeof(*pipex));
	if (!pipex)
		return (NULL);
	pipex->pipe_index = FIRST_PIPE;
	pipex->fdpipe_index = 0;
	pipex->in_fd = -1;
	return (pipex);
}

void	pipe_struct_update(t_shell *shell, t_pipe *pipex, size_t i)
{
	if (i < shell->nb_pipe - 1)
	{
		pipex->pipe_index = N_PIPE;
		pipex->fdpipe_index += 2;
	}
	else
		pipex->pipe_index = LAST_PIPE;
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	pipex->in_fd = dup(pipex->fdpipe[0]);
	close(pipex->fdpipe[0]);
	close(pipex->fdpipe[1]);
}
