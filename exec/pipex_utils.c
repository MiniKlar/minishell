#include "minishell.h"

bool	init_pipe(t_pipe *pipex, size_t nb_pipe);

t_pipe	*init_struct_pipex(size_t nb_pipe)
{
	t_pipe	*pipex;

	pipex = malloc(sizeof(*pipex));
	if (!pipex)
	{
		printf("Error malloc struct pipex");
		return (NULL);
	}
	pipex->pipe_index = FIRST_PIPE;
	pipex->fdpipe_index = 0;
	if (nb_pipe == 1)
	{
		pipex->fdpipe = malloc(sizeof(int) * (2 + 1));
		if (pipex->fdpipe == NULL)
		{
			printf("Error malloc fd pipes");
			return (NULL);
		}
	}
	else if (nb_pipe > 1)
	{
		pipex->fdpipe = malloc(sizeof(int) * 3);
		pipex->fdpipe2 = malloc(sizeof(int) * 3);
		if (pipex->fdpipe == NULL || pipex->fdpipe2 == NULL)
		{
			printf("Error malloc fd pipes");
			return (NULL);
		}
	}
	return (pipex);
}

bool	init_pipe(t_pipe *pipex, size_t nb_pipe)
{
	if (nb_pipe == 1)
		pipex->fdpipe[2] = 0;
	else if (nb_pipe > 1)
		pipex->fdpipe2[2] = 0;
	if (pipe((pipex->fdpipe)) == -1)
	{
		perror("Error init pipe");
		return (false);
	}
	return (true);
}

//

void	pipe_struct_update(t_shell *shell, t_pipe *pipex, size_t i)
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


//
