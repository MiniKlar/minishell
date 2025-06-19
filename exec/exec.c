#include <minishell.h>

bool	built_ins_1(t_shell *shell);

void	exec_no_command(t_shell *shell)
{
	if (shell->cmd->redir)
	{
		ft_dup_std(shell);
		redir_cmd_input_output(shell);
		ft_dup_redir(shell, false);
		ft_dup_std_back(shell);
	}
}

bool	exec_built_in(t_shell *shell, bool is_child)
{
	if (!is_child)
		shell->is_child = false;
	else
		shell->is_child = true;
	if (!is_cmd_built_ins(shell) && is_child == false)
		return (false);
	if (!is_child)
	{
		ft_dup_std(shell);
		redir_cmd_input_output(shell);
		ft_dup_redir(shell, false);
	}
	built_ins_1(shell);
	if (!is_child)
		ft_dup_std_back(shell);
	return (true);
}

void	exec(t_shell *shell)
{
	if ((!shell->cmd->cmd && shell->nb_pipe == 0) || check_if_directory(shell))
		return (exec_no_command(shell));
	else if (shell->nb_pipe == 0 && exec_built_in(shell, false) == true)
		return ;
	else
	{
		shell->is_child = true;
		exec_cmd(shell);
	}
}

bool	built_ins_2(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd[0], "pwd", 4) == 0)
		shell->exit_code = ft_pwd(shell, true);
	else if ((ft_strncmp(shell->cmd->cmd[0], "echo", 5) == 0))
		shell->exit_code = ft_echo(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "env", 4) == 0)
		shell->exit_code = ft_env(shell);
	else
		return (false);
	return (true);
}

bool	built_ins_1(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
		return (false);
	if (ft_strncmp(shell->cmd->cmd[0], "export", 5) == 0)
		shell->exit_code = ft_export(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "cd", 3) == 0)
		shell->exit_code = ft_cd(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "unset", 6) == 0)
		shell->exit_code = ft_unset(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "exit", 5) == 0)
		ft_exit(shell);
	else if (built_ins_2(shell) == false)
		return (false);
	return (true);
}

bool	is_cmd_built_ins(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
		return (false);
	else if (ft_strncmp(shell->cmd->cmd[0], "export", 7) == 0)
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
