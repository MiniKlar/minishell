#include "minishell.h"

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

	if (shell->nb_pipe > 0)
		shell->pipex = set_struct_pipex(shell);
	else
		shell->pipex = NULL;
	shell->id_fork = fork_cmd(shell);
	create_children(shell);
	ft_wait(shell, shell->nb_pipe, &wstatus);
	set_signals_interactive();
	if (WIFEXITED(wstatus) == true && WEXITSTATUS(wstatus))
	{
		free(shell->pipex);
		free(shell->id_fork);
		shell->exit_code = WEXITSTATUS(wstatus);
		return (0);
	}
	free(shell->pipex);
	free(shell->id_fork);
	return (0);
}
