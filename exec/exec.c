#include <minishell.h>

bool	built_ins_1(t_shell *shell);

bool	exec_no_command(t_shell *shell)
{
	if (shell->cmd->cmd == NULL)
	{
		shell->wstatus = 0;
		if (shell->cmd->redir)
		{
			//printf("TU RENTRES ICI ET CEST LA MERDE\n");
			redir_cmd_input_output(shell);
			ft_dup_redir(shell, false);
			ft_dup_std_back(shell);
		}
		return(true);
	}
	else
		return(false);
}

bool	exec_built_in(t_shell *shell, bool is_child)
{
	if (!is_child)
		shell->is_child = false;
	else
		shell->is_child = true;
	if (!is_cmd_built_ins(shell) && is_child == false) //si ce n'est pas un built-in
		return (false);	//je retourne false
	if (!is_child) //si ce n'est pas un child
	{
		ft_dup_std(shell); //on dup stdin et stdout pour les sauvegarder.
		redir_cmd_input_output(shell); //redirection in et out (infile, outfile, heredoc)
		ft_dup_redir(shell, false);
	}
	built_ins_1(shell);
	if (!is_child)
		ft_dup_std_back(shell);
	return (true);

	//REVOIR LE FONCTIONNEMENT DES REDIR TOTALS avec built-ins.
}

void	exec(t_shell *shell)
{
	if (exec_no_command(shell) == true)
		return ;
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
