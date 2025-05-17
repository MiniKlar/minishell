#include "minishell.h"

void	create_children(t_shell *node, t_pipe *pipex);
int		ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes);
pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex);
void	redir_cmd_input_output(t_shell *shell);
int		ft_dup(t_pipe *pipex);
void	ft_dup_redir(t_shell *shell);

int	exec_cmd(t_shell *shell)
{
	t_pipe	*pipex;
	pid_t	*id_fork;

	pipex = init_struct_pipex(shell->nb_pipe);
	if (!pipex)
	{
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
	id_fork = fork_cmd(shell, pipex);
	if (pipex->fdpipe != NULL)
		ft_close_fdpipe(pipex);
	shell->wstatus = ft_wait(shell, id_fork, shell->nb_pipe);
	if (WIFEXITED(shell->wstatus) && WEXITSTATUS(shell->wstatus))
		return (WEXITSTATUS(shell->wstatus));
	free(id_fork);
	free_struct_pipe(pipex);
	return (0);
}

pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex)
{
	size_t	i;
	size_t	nb_fork;
	pid_t	*id_fork;

	if (shell->nb_pipe == 0)
		nb_fork = 1;
	else
		nb_fork = shell->nb_pipe;
	id_fork = malloc(sizeof(pid_t) * (nb_fork + 1));
	id_fork[nb_fork] = 0;
	if (!id_fork)
		free_all(shell, pipex);
	i = 0;
	while (shell->cmd)
	{
		id_fork[i] = fork();
		if (id_fork[i] == -1)
		{
			free(id_fork);
			free_all(shell, pipex);
		}
		else if (id_fork[i] == 0)
			create_children(shell, pipex);
		if (WEXITSTATUS(shell->wstatus) == 127)
			exit(shell->wstatus);
		pipe_struct_update(shell, pipex, i);
		shell->cmd = shell->cmd->next;
		i++;
	}
	return (id_fork);
}

void	create_children(t_shell *shell, t_pipe *pipex)
{
	char	*command_path;

	command_path = check_command_path(shell->cmd->cmd[0], shell->envp);
	if (command_path == NULL)
	{
		free_all(shell, pipex);
		exit(127);
	}
	redir_cmd_input_output(shell);
	if (shell->nb_pipe != 0)
	{
		if (ft_dup(pipex) == -1)
		{
			free_all(shell, pipex);
			free(command_path);
			exit(1);
		}
		ft_close_fdpipe(pipex);
	}
	else
		ft_dup_redir(shell);
	if (execve(command_path, &shell->cmd->cmd[0], shell->envp) == -1)
	{
		perror("ERROR EXEC VE");
		free_all(shell, pipex);
		free(command_path);
		exit(126);
	}
}

void	redir_cmd_input_output(t_shell *shell)
{
	char		*heredoc_name;
	e_symbol	type_redir;
	int			i;

	i = 0;
	heredoc_name = NULL;
	while (shell->redir != NULL)
	{
		type_redir = shell->redir->symbol;
		if (type_redir == REDIR_IN)
			redir_infile(shell);
		else if (type_redir == REDIR_OUT || type_redir == APPEND)
			redir_outfile(shell);
		else if (type_redir == HERE_DOC)
		{
			heredoc_name = here_doc(shell, i);
			if (heredoc_name)
				unlink(heredoc_name);
			i++;
		}
		shell->redir = shell->redir->next;
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

void	ft_dup_redir(t_shell *shell)
{
	if (shell->fd_in != STDIN_FILENO)
		dup2(shell->fd_in, STDIN_FILENO);
	if (shell->fd_out != STDOUT_FILENO)
		dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd_in);
	close(shell->fd_out);
}

int	ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes)
{
	size_t	i;

	i = 0;
	while (i < nb_pipes + 1)
	{
		if (waitpid(id_fork[i], &shell->wstatus, 0) == -1)
		{
			perror("waitpid error");
			exit(1);
		}
		i++;
	}
	return (shell->wstatus);
}
