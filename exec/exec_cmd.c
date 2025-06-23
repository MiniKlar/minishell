#include "minishell.h"

void	create_child(t_shell *shell);
void	create_children(t_shell *shell);
pid_t	*fork_cmd(t_shell *shell);
int		dup_pipe(t_shell *shell);

void	create_fdpipe(t_shell *shell)
{
	if (shell->nb_pipe > 0)
	{
		if (pipe(shell->pipex->fdpipe) == -1)
		{
			perror("pipe");
			free_all(shell);
			exit(EXIT_FAILURE);
		}
	}
}

int	exec_cmd(t_shell *shell)
{
	int	wstatus;
	int	sig;

	if (shell->nb_pipe > 0)
		shell->pipex = set_struct_pipex(shell);
	else
		shell->pipex = NULL;
	shell->id_fork = fork_cmd(shell);
	create_children(shell);
	ft_wait(shell, shell->nb_pipe, &wstatus);
	if (WIFSIGNALED(wstatus))
	{
		sig = WTERMSIG(wstatus);
		shell->exit_code = 128 + sig;
		if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if (WIFEXITED(wstatus))
	{
		shell->exit_code = WEXITSTATUS(wstatus);
	}
	free(shell->pipex);
	free(shell->id_fork);
	return (0);
}

pid_t	*fork_cmd(t_shell *shell)
{
	size_t	nb_fork;
	pid_t	*id_fork;

	if (shell->nb_pipe == 0)
		nb_fork = 1;
	else
		nb_fork = shell->nb_pipe + 1;
	id_fork = malloc(sizeof(pid_t) * nb_fork);
	if (!id_fork)
	{
		printf("Error malloc id_fork");
		free_all(shell);
	}
	return (id_fork);
}

void	create_children(t_shell *shell)
{
	size_t	i;
	t_cmd	*tmp;

	i = 0;
	set_signals_exec();
	tmp = shell->cmd;
	while (shell->cmd != NULL)
	{
		create_fdpipe(shell);
		shell->id_fork[i] = fork();
		if (shell->id_fork[i] == -1)
		{
			printf("Error fork id_fork[%zu]", i);
			ft_exit(shell);
		}
		if (shell->id_fork[i] == 0)
		{
			set_signals_default();
			create_child(shell);
		}
		if (shell->id_fork[i] != 0)
		{
			if (shell->nb_pipe > 0)
				pipe_struct_update(shell, i);
			shell->cmd = shell->cmd->next;
			i++;
		}
	}
	if (shell->pipex)
	{
		if (shell->pipex->in_fd != -1)
			close(shell->pipex->in_fd);
	}
	shell->cmd = tmp;
	set_signals_interactive();
}

void	create_child(t_shell *shell)
{
	char	*command_path;
	bool	is_built_ins;

	command_path = NULL;
	is_built_ins = is_cmd_built_ins(shell);
	if (!is_built_ins && shell->cmd->cmd)
		command_path = find_command_exist_executable(shell);
	if (!redir_cmd_input_output(shell))
	{
		free_child(shell, command_path);
		exit(1);
	}
	ft_dup_redir(shell, true);
	if (shell->nb_pipe > 0)
		ft_dup(shell, command_path);
	if (is_built_ins)
	{
		exec_built_in(shell, true);
		free_child(shell, command_path);
		exit(EXIT_SUCCESS);
	}
	if (shell->cmd->cmd)
	{
		if (execve(command_path, &shell->cmd->cmd[0], shell->envp) == -1)
		{
			perror("ERROR EXEC VE");
			free_child(shell, command_path);
			exit(126);
		}
	}
	free_child(shell, command_path);
	exit(EXIT_SUCCESS);
}

void	ft_dup_std_back(t_shell *shell)
{
	dup2(shell->tmp_stdin, STDIN_FILENO);
	dup2(shell->tmp_stdout, STDOUT_FILENO);
	close(shell->tmp_stdin);
	close(shell->tmp_stdout);
	shell->tmp_stdin = -1;
	shell->tmp_stdout = -1;
}

void	ft_dup_std(t_shell *shell)
{
	shell->tmp_stdin = dup(STDIN_FILENO);
	shell->tmp_stdout = dup(STDOUT_FILENO);
}

bool	redir_cmd_input_output(t_shell *shell)
{
	char		*heredoc_name;
	t_symbol	type_redir;
	t_redir		*tmp_redir;
	int			i;

	i = 0;
	heredoc_name = NULL;
	if (!shell->cmd->redir)
		return (true);
	else
		tmp_redir = shell->cmd->redir;
	while (shell->cmd->redir != NULL)
	{
		type_redir = shell->cmd->redir->symbol;
		if (type_redir == REDIR_IN)
		{
			if (!redir_infile(shell))
				return (false);
		}
		else if (type_redir == REDIR_OUT || type_redir == APPEND)
		{
			if (!redir_outfile(shell))
				return (false);
		}
		else if (type_redir == HERE_DOC)
		{
			heredoc_name = here_doc(shell, i);
			if (heredoc_name)
			{
				unlink(heredoc_name);
				free(heredoc_name);
			}
			else
				return (false);
			i++;
		}
		shell->cmd->redir = shell->cmd->redir->next;
	}
	shell->cmd->redir = tmp_redir;
	return (true);
}

void	ft_dup(t_shell *shell, char *command_path)
{
	if (dup_pipe(shell) == -1)
	{
		printf("error dup_pipe\n");
		free_array(shell->envp);
		free_all(shell);
		free(shell);
		if (command_path)
			free(command_path);
		exit(1);
	}
	if (shell->pipex->in_fd != -1)
	{
		close(shell->pipex->in_fd);
		shell->pipex->in_fd = -1;
	}
	close(shell->pipex->fdpipe[0]);
	close(shell->pipex->fdpipe[1]);
}

int	dup_pipe(t_shell *shell)
{
	int	p;

	p = shell->pipex->pipe_index;
	if (p == FIRST_PIPE)
	{
		if (shell->fd_out == -1)
		{
			if (dup2(shell->pipex->fdpipe[1], STDOUT_FILENO) == -1)
			{
				printf("Error dup2 --> FIRST_PIPE\n");
				return (-1);
			}
		}
	}
	else if (p == N_PIPE)
	{
		if (shell->fd_in == -1)
		{
			if (dup2(shell->pipex->in_fd, STDIN_FILENO) == -1)
			{
				printf("Error dup2 --> N_PIPE STDIN\n");
				return (-1);
			}
		}
		if (shell->fd_out == -1)
		{
			if (dup2(shell->pipex->fdpipe[1], STDOUT_FILENO) == -1)
			{
				printf("Error dup2 --> N_PIPE STDOUT\n");
				return (-1);
			}
		}
	}
	else if (p == LAST_PIPE)
	{
		if (shell->fd_in == -1)
		{
			if (dup2(shell->pipex->in_fd, STDIN_FILENO) == -1)
			{
				printf("Error dup2 --> LAST_PIPE STDIN\n");
				return (-1);
			}
		}
	}
	return (0);
}

void	ft_dup_redir(t_shell *shell, bool is_child)
{
	if (shell->fd_in > -1)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
		shell->fd_in = -1;
	}
	if (shell->fd_out > -1)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
		shell->fd_out = -1;
	}
	if (shell->tmp_stdin > -1 && is_child == true)
	{
		close(shell->tmp_stdin);
		shell->tmp_stdin = -1;
	}
	if (shell->tmp_stdout > -1 && is_child == true)
	{
		close(shell->tmp_stdout);
		shell->tmp_stdout = -1;
	}
}
