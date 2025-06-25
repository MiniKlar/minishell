#include "minishell.h"

void	free_ctrl_d(t_shell *shell)
{
	free_all(shell);
	free_array(shell->envp);
	free(shell);
	write(STDOUT_FILENO, "exit\n", 5);
}

int	main(void)
{
	t_shell	*shell;

	shell = init_shell(environ);
	get_shell_context(shell);
	set_signals_interactive();
	while (1)
	{
		shell->readline_cmd = readline("minishell$ ");
		if (shell->readline_cmd == NULL)
		{
			free_ctrl_d(shell);
			exit(0);
		}
		if (parsing(shell, shell->readline_cmd) == true)
		{
			exec(shell);
			free_shell(shell);
		}
		if (ft_strncmp(shell->readline_cmd, "", 1) != 0)
			add_history(shell->readline_cmd);
		environ = shell->envp;
		if (shell->readline_cmd)
		{
			free(shell->readline_cmd);
			shell->readline_cmd = NULL;
		}
	}
	return (shell->exit_code);
}
