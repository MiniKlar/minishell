#include "minishell.h"

static bool	is_directory(char *str, DIR *dir)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			break ;
	}
	if (str[i] == '\0')
		return (false);
	dir = opendir(str);
	if (dir != NULL)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is directory\n", 2);
		closedir(dir);
	}
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (true);
}

bool	check_if_directory(t_shell *shell)
{
	if (!shell->cmd->cmd)
		return (false);
	if (shell->cmd->cmd[0][0] == '.' && shell->cmd->cmd[0][1] == '\0')
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(shell->cmd->cmd[0], 2);
		ft_putstr_fd(": filename argument required ", 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd(shell->cmd->cmd[0], 2);
		ft_putstr_fd(": usage: . filename [arguments]\n", 2);
		shell->exit_code = 2;
		return (true);
	}
	else
	{
		if ((access(shell->cmd->cmd[0], X_OK) == -1)
			&& is_directory(shell->cmd->cmd[0], NULL))
		{
			shell->exit_code = 126;
			return (true);
		}
	}
	return (false);
}

t_pipe	*set_struct_pipex(t_shell *shell)
{
	t_pipe	*pipex;

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
	char	*command_path;

	command_path = check_command_path(shell->cmd->cmd[0], shell->envp);
	if (command_path == NULL)
	{
		if (ft_strncmp(shell->cmd->cmd[0], "", 1) == 0)
			printf("bash:%s: command not found\n", shell->cmd->cmd[0]);
		else
			printf("bash: %s: command not found\n", shell->cmd->cmd[0]);
		free_array(shell->envp);
		if (shell->pipex)
		{
			if (shell->pipex->in_fd != -1)
				close(shell->pipex->in_fd);
			close(shell->pipex->fdpipe[0]);
			close(shell->pipex->fdpipe[1]);
		}
		free_all(shell);
		free(shell);
		exit(127);
	}
	else
		return (command_path);
}

int	ft_wait(t_shell *shell, size_t nb_pipes, int *wstatus)
{
	size_t	i;

	i = 0;
	while (i != nb_pipes + 1)
	{
		if (waitpid(shell->id_fork[i], wstatus, 0) == -1)
		{
			perror("waitpid error");
			exit(1);
		}
		i++;
	}
	return (0);
}
