#include "minishell.h"

t_pipe	*set_struct_pipex(t_shell *shell)
{
	t_pipe *pipex;

	pipex = init_struct_pipex();
	if (!pipex)
	{
		printf("Error alloc pipex");
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
	return (pipex);
}
char	*find_command_exist_executable(t_shell *shell)
{
	char *command_path;

	command_path = check_command_path(shell->cmd->cmd[0], shell->envp);
	if (command_path == NULL)
	{
		printf("bash: %s: command not found\n", shell->cmd->cmd[0]);
		free_array(shell->envp);
		free_all(shell);
		free(shell);
		exit(127);
	}
	else
		return (command_path);
}

int	ft_wait(t_shell *shell, size_t nb_pipes)
{
	// size_t	i;

	// i = 0;
	(void)nb_pipes;
	if (waitpid(shell->id_fork[0], &shell->wstatus, 0) == -1)
		perror("waitpid error");
	if (waitpid(shell->id_fork[1], &shell->wstatus, 0) == -1)
		perror("waitpid error");
	// while (i < nb_pipes + 1)
	// {
	// 	if (waitpid(shell->id_fork[0], &shell->wstatus, 0) == -1)
	// 	{
	// 		perror("waitpid error");
	// 		exit(1);
	// 	}
	// 	i++;
	// }
	return (shell->wstatus);
}
