#include <minishell.h>

bool	is_cmd_built_ins(t_shell *shell, char **envp);
bool	exec_shell_param(t_shell *shell, char **envp);

void	exec(t_shell *shell, char **envp)
{
	if (is_cmd_built_ins(shell, envp) == true)
		printf("Built-ins executed\n");
	else if (exec_shell_param(shell, envp) == true)
		printf("Shell parameters added to envp\n");
	else
		exec_cmd(shell, envp);
}

bool	is_cmd_built_ins(t_shell *shell, char **envp)
{
	char	*buffer;

	buffer = NULL;
	if (ft_strncmp(shell->cmd[0], "export", 5) == 0)
	{
		export(shell, envp);
		return (true);
	}
	else if (ft_strncmp(shell->cmd[0], "pwd", 3) == 0)
	{
		buffer = pwd(true);
		free(buffer);
		return (true);
	}
	else if (ft_strncmp(shell->cmd[0], "cd", 2) == 0)
	{
		cd(shell, envp);
		return (true);
	}
	else if ((ft_strncmp(shell->cmd[0], "echo ", 5) == 0))
	{
		//ft_echo(tab_cmd, node);
		return (true);
	}
	else if (ft_strncmp(shell->cmd[0], "exit", 4) == 0)
	{
		ft_exit(shell);
		return (true);
	}
	else if (ft_strncmp(shell->cmd[0], "env", 3) == 0)
	{
		env(envp);
		return (true);
	}
	return (false);
}

bool	exec_shell_param(t_shell *shell, char **envp)
{
	if (is_shell_parameter(shell) == false)
		return (false);
	else
		append_envp(shell->cmd[0], envp);
	return (true);
}
