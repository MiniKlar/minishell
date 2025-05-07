#include "minishell.h"

int		ft_wait(t_pipe *pipex, pid_t *id_fork, size_t nb_pipes);
void	fork_pipex(t_token *node, t_pipe *pipex, char **envp);
void	pipe_struct_update(t_pipe *pipex, size_t i);
void	ft_close_fdpipe(t_pipe *pipex);
int		ft_dup(t_pipe *pipex);

t_token *move_tokptr(t_token *tokens)
{
	bool	is_pipe;

	is_pipe = false;
	while(is_pipe == false && tokens) 
	{
		if (tokens->is_pipe == true)
			is_pipe = true;
		else
			tokens = tokens->next;
	}
	if (tokens != NULL)
		tokens = tokens->next;
	return (tokens);
}

t_pipe *init_struct_pipex(t_token *tokens, t_pipe *pipex)
{
	size_t	i;

	i = 0;
	pipex = malloc(sizeof(*pipex));
	if (!pipex)
		exit(EXIT_FAILURE);
	pipex->pipe_index = FIRST_PIPE;
	pipex->fdpipe_index = 0;
	pipex->wstatus = 0;
	pipex->nb_pipe = print_pipes_nbr(tokens);
	pipex->fdpipe = malloc(sizeof(int) * ((pipex->nb_pipe * 2) + 1));
	if (pipex->fdpipe == NULL)
	{
		free(pipex);
		exit(EXIT_FAILURE);
	}
	pipex->fdpipe[pipex->nb_pipe * 2] = 0;
	while (i < pipex->nb_pipe * 2)
	{
		if (pipe(((pipex->fdpipe) + i)) == -1)
		{
			perror("Error pipe");
			free(pipex);
			exit(EXIT_FAILURE);
		}
		i += 2;
	}
	return(pipex);
}
int ft_pipe(t_token *tokens, char **envp)
{
	t_pipe *pipex;
	size_t i;

	pipex = NULL;
	pipex = init_struct_pipex(tokens, pipex);
	pid_t	id_fork[pipex->nb_pipe];
	i = 0;
	while(i < pipex->nb_pipe + 1)
	{
		id_fork[i] = fork();
		if (id_fork[i] == -1)
			free(pipex);
		else if (id_fork[i] == 0)
			fork_pipex(tokens, pipex, envp);
		if (WEXITSTATUS(pipex->wstatus) == 127)
			exit(WEXITSTATUS(pipex->wstatus) == 127);
		pipe_struct_update(pipex, i);
		tokens = move_tokptr(tokens);
		i++;
	}
	ft_close_fdpipe(pipex);
	pipex->wstatus = ft_wait(pipex, id_fork, pipex->nb_pipe);
	if (WIFEXITED(pipex->wstatus) && WEXITSTATUS(pipex->wstatus))
		return (WEXITSTATUS(pipex->wstatus));
	free_struct_pipe(pipex);
	return (EXIT_SUCCESS);
}

void	fork_pipex(t_token *node, t_pipe *pipex, char **envp)
{
	char	**command_arg;
	char	*command_path;

	command_arg = recup_command_arg(node);
	command_path = check_command_path(node->tokens, envp);
	// check both cmd to clear memory if error
	if (ft_dup(pipex) == -1)
	{
		free_execve_error(node, pipex, command_arg, command_path);
		exit(1);
	}
	ft_close_fdpipe(pipex);
	if (execve(command_path, &command_arg[0], envp) == -1)
	{
		perror("ERROR EXEC VE");
		free_execve_error(node, pipex, command_arg, command_path);
		exit(127);
	}
}

int	ft_dup(t_pipe *pipex)
{
	int i;
	int	p;

	i = pipex->fdpipe_index;
	p = pipex->pipe_index;
	if (p == FIRST_PIPE)
	{
		if (dup2(pipex->fdpipe[i + 1], 1) == -1)
			return (-1);
	}
	else if (p == N_PIPE)
	{
		if (dup2(pipex->fdpipe[i - 2], 0) == -1 || dup2(pipex->fdpipe[i + 1], 1) == -1)
			return (-1);
	}
	else if (p == LAST_PIPE)
	{
		if (dup2(pipex->fdpipe[i], 0) == -1)
			return (-1);
	}
	return (0);
}

void	pipe_struct_update(t_pipe *pipex, size_t i)
{
	if (i < pipex->nb_pipe - 1)
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

int	ft_wait(t_pipe *pipex, pid_t *id_fork, size_t nb_pipes)
{
	size_t	i;

	i = 0;
	while (i < nb_pipes + 1)
	{
		if (waitpid(id_fork[i], &pipex->wstatus, 0) == -1)
		{
			perror("waitpid error");
			exit(1);
		}
		i++;
	}
	return (pipex->wstatus);
}
