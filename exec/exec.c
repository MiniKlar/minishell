#include <minishell.h>

void	exec(t_shell *shell)
{
	if (shell->cmd->next == NULL && is_cmd_built_ins(shell) == true)
		exec_built_in(shell);
	else
		exec_cmd(shell);
}

bool	exec_built_in_inside_child(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd[0], "pwd", 4) == 0)
		shell->wstatus = ft_pwd(true);
	else if ((ft_strncmp(shell->cmd->cmd[0], "echo", 5) == 0))
		shell->wstatus = ft_echo(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "env", 4) == 0)
		shell->wstatus = ft_env(shell);
	else
		return (false);
	return (true);
}

int	exec_built_in(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd[0], "export", 5) == 0)
		shell->wstatus = ft_export(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "cd", 3) == 0)
		shell->wstatus = ft_cd(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "unset", 6) == 0)
		shell->wstatus = ft_unset(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "exit", 5) == 0)
		ft_exit(shell);
	else if (exec_built_in_inside_child(shell) == false)
		return (false);
	return (0);
}

bool	is_cmd_built_ins(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd[0], "export", 5) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "cd", 3) == 0)
		return (true);
	else if ((ft_strncmp(shell->cmd->cmd[0], "echo", 5) == 0))
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "env", 4) == 0)
		return (true);
	else if (ft_strncmp(shell->cmd->cmd[0], "unset", 6) == 0)
		return (true);
	return (false);
}
