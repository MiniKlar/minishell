#include <minishell.h>

void	exec(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
	{
		shell->wstatus = 0;
		return ;
	}
	if (shell->cmd->next == NULL && is_cmd_built_ins(shell) == true)
		exec_built_in(shell, false);
	else
		exec_cmd(shell);
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
	int	tmp_stdin;
	int	tmp_stdout;

	if (!is_cmd_built_ins(shell))
		return (1);
	if (!is_child)
	{
		tmp_stdin = dup(STDIN_FILENO);
		tmp_stdout = dup(STDOUT_FILENO);
	}
	redir_cmd_input_output(shell); //redirection in et out (infile, outfile, heredoc)
	ft_dup_redir(shell); //dup le fd_in et fd_out
	built_ins_1(shell);
	if (!is_child)
	{
		dup2(tmp_stdin, STDIN_FILENO);
		dup2(tmp_stdout, STDOUT_FILENO);
		close(tmp_stdin);
		close(tmp_stdout);
	}
	return (0);
}

bool	is_cmd_built_ins(t_shell *shell)
{
	if (ft_strncmp(shell->cmd->cmd[0], "export", 7) == 0)
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
