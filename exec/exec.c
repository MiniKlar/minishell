#include <minishell.h>

void	exec(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
	{
		shell->wstatus = 0;
		if (shell->cmd->redir)
		{
			redir_cmd_input_output(shell);
			ft_dup_redir(shell);
			ft_dup_std_back(shell);
		}
		else
			return ;
	}
	else if (shell->cmd->next == NULL && is_cmd_built_ins(shell) == true)
	{
		printf("tu exec built in\n");
		shell->is_child = false;
		exec_built_in(shell, false);
	}
	else
	{
		printf("tu exec cmd\n");
		shell->is_child = true;
		exec_cmd(shell);
	}
}

bool	built_ins_2(t_shell *shell)
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

bool	built_ins_1(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
		return (false);
	if (ft_strncmp(shell->cmd->cmd[0], "export", 5) == 0)
		shell->wstatus = ft_export(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "cd", 3) == 0)
		shell->wstatus = ft_cd(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "unset", 6) == 0)
		shell->wstatus = ft_unset(shell);
	else if (ft_strncmp(shell->cmd->cmd[0], "exit", 5) == 0)
		ft_exit(shell);
	else if (built_ins_2(shell) == false)
		return (false);
	return (true);
}

int	exec_built_in(t_shell *shell, bool is_child)
{
	if (!is_cmd_built_ins(shell))
		return (1);
	if (!is_child)
		ft_dup_std(shell);
	redir_cmd_input_output(shell);
	ft_dup_redir(shell);
	built_ins_1(shell);
	if (!is_child)
		ft_dup_std_back(shell);
	return (0);
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
