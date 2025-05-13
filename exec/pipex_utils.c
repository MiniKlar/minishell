#include "minishell.h"

bool	init_pipe(t_pipex *pipex);

t_pipe	*init_struct_pipex(size_t nb_pipe)
{
	t_pipe	*pipex;

	pipex = malloc(sizeof(*pipex));
	if (!pipex)
		return (NULL);
	pipex->pipe_index = FIRST_PIPE;
	pipex->fdpipe_index = 0;
	if (nb_pipe > 0)
	{
		pipex->fdpipe = malloc(sizeof(int) * ((pipex->nb_pipe * 2) + 1));
		if (pipex->fdpipe == NULL)
			return (NULL);
		if (init_pipe(pipex) == false)
			return (NULL);
	}
	return (pipex);
}

bool	init_pipe(t_pipex *pipex)
{
	size_t	i;

	i = 0;
	pipex->fdpipe[pipex->nb_pipe * 2] = 0;
	while (i < pipex->nb_pipe * 2)
	{
		if (pipe(((pipex->fdpipe) + i)) == -1)
		{
			perror("Error init pipe");
			return (false);
		}
		i += 2;
	}
	return (true);
}

void	pipe_struct_update(t_shell *shell, size_t i)
{
	if (i < shell->nb_pipe - 1)
	{
		pipex->pipe_index = N_PIPE;
		pipex->fdpipe_index += 2;
	}
	else
		pipex->pipe_index = LAST_PIPE;
}

void	ft_close_fdpipe(t_pipe *pipex)
{
	size_t	i;

	i = 0;
	while (pipex->fdpipe[i] != 0)
	{
		close(pipex->fdpipe[i]);
		i++;
	}
}
