#include "minishell.h"

void	create_children(t_shell *node, t_pipe *pipex, char **envp);
int		ft_wait(t_pipe *pipex, pid_t *id_fork, size_t nb_pipes);
void	fork_cmd(t_shell *shell, t_pipe *pipex, char **envp);
int		ft_dup(t_pipe *pipex);

int	exec_cmd(t_shell *shell, char **envp)
{
	t_pipe	*pipex;
	pid_t	*id_fork;

	pipex = init_struct_pipex(shell->nb_pipe);
	if (!pipex)
	{
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
	id_fork = fork_cmd(shell, pipex, envp);
	if (pipex->fdpipe != NULL)
		ft_close_fdpipe(pipex);
	pipex->wstatus = ft_wait(pipex, id_fork, shell->nb_pipe);
	if (WIFEXITED(shell->wstatus) && WEXITSTATUS(shell->wstatus))
		return (WEXITSTATUS(shell->wstatus));
	free(id_fork);
	free_struct_pipe(pipex);
	return (0);
}

pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex, char **envp)
{
	size_t	i;
	pid_t	*id_fork;

	id_fork = malloc(sizeof(pid_t) * shell->nb_pipe);
	if (!id_fork)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < shell->nb_pipe + 1)
	{
		id_fork[i] = fork();
		if (id_fork[i] == -1)
			free_all(shell, pipex);
		else if (id_fork[i] == 0)
			create_children(shell, pipex, envp);
		if (WEXITSTATUS(shell->wstatus) == 127)
			exit(WEXITSTATUS(shell->wstatus) == 127);
		pipe_struct_update(pipex, i);
		if (shell != NULL)
			shell = shell->shell;
		i++;
	}
}

void	create_children(t_shell *shell, t_pipe *pipex, char **envp)
{
	char	*command_path;

	command_path = check_command_path(shell->cmd[0], envp);
	if (command_path == NULL)
	{
		free_all(shell, pipex);
		exit(1);
	}
	redir_cmd_input_output(shell);
	if (shell->nb_pipe != 0)
	{
		if (ft_dup(pipex) == -1)
		{
			free_execve_error(shell, pipex, command_path);
			exit(1);
		}
		ft_close_fdpipe(pipex);
	}
	if (execve(command_path, &shell->cmd[0], envp) == -1)
	{
		perror("ERROR EXEC VE");
		free_execve_error(shell, pipex, command_path);
		exit(126);
	}
}

void	redir_cmd_input_output(t_shell *shell)
{
	while (shell->redir != NULL)
	{
		if (shell->redir->symbol == REDIR_IN)
			open_access_infile(shell->redir->str);
		else if (shell->redir->symbol == REDIR_OUT)
			open_access_outfile(shell->redir->str);
		else if (shell->redir->symbol == HERE_DOC)
			here_doc(shell);
		else if (shell->redir->symbol == APPEND)
			open_append_access_outfile(shell->redir->str);
		shell->redir = shell->redir->t_redir;
	}
}

int	ft_dup(t_pipe *pipex)
{
	int	i;
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
		if (dup2(pipex->fdpipe[i - 2], 0) == -1
			|| dup2(pipex->fdpipe[i + 1], 1) == -1)
			return (-1);
	}
	else if (p == LAST_PIPE)
	{
		if (dup2(pipex->fdpipe[i], 0) == -1)
			return (-1);
	}
	return (0);
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
