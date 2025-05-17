#include <minishell.h>

bool	is_cmd_built_ins(t_shell *shell);
bool	exec_shell_param(t_shell *shell);

void	exec(t_shell *shell)
{
	if (is_cmd_built_ins(shell) == true)
		;
		// printf("Built-ins executed\n");
	// else if (exec_shell_param(shell) == true)
	// 	printf("Shell parameters added to envp\n");
	else
		exec_cmd(shell);
}

bool	is_cmd_built_ins(t_shell *shell)
{
	char	*buffer;

	buffer = NULL;
	if (ft_strncmp(shell->cmd->cmd[0], "export", 5) == 0)
	{
		shell->wstatus = ft_export(shell);
		return (true);
	}
	if (ft_strncmp(shell->cmd->cmd[0], "pwd", 4) == 0)
	{
		ft_pwd(shell, true);
		return (true);
	}
	else if (ft_strncmp(shell->cmd->cmd[0], "cd", 3) == 0)
	{
		shell->wstatus = ft_cd(shell);
		return (true);
	}
	else if ((ft_strncmp(shell->cmd->cmd[0], "echo", 5) == 0))
	{
		ft_echo(shell);
		return (true);
	}
	else if (ft_strncmp(shell->cmd->cmd[0], "exit", 5) == 0)
	{
		ft_exit(shell);
		return (true);
	}
	else if (ft_strncmp(shell->cmd->cmd[0], "env", 4) == 0)
	{
		ft_env(shell);
		return (true);
	}
	else if (ft_strncmp(shell->cmd->cmd[0], "unset", 6) == 0)
	{
		shell->wstatus = ft_unset(shell);
		return (true);
	}
	return (false);
}

// bool	exec_shell_param(t_shell *shell)
// {
// 	if (is_shell_parameter(shell) == false)
// 		return (false);
// 	else
// 		append_envp(shell->cmd->cmd[0]);
// 	return (true);
// }
