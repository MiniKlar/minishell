#include "minishell.h"

void	free_ctrl_d(t_shell *shell)
{
	free_array(shell->envp);
	free(shell);
	write(STDOUT_FILENO, "exit\n", 5);
}

int	main(void)
{
	t_shell	*shell;
	char	*command;

	shell = init_shell(environ);
	get_shell_context(shell);
	set_signals_interactive();
	while (1)
	{
		command = readline("minishell$ ");
		if (command == NULL)
		{
			free_ctrl_d(shell);
			exit(0);
		}
		if (parsing(shell, command) == true)
		{
			exec(shell);
			free_shell(shell);
		}
		if (ft_strncmp(command, "", 1) != 0)
			add_history(command);
		free(command);
		environ = shell->envp;
	}
	return (shell->exit_code);
}
