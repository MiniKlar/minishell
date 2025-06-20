#include "minishell.h"

volatile sig_atomic_t g_child_running = 0;

int main(void)
{
	t_shell *shell;
	char *command;

	shell = init_shell(environ);
	set_signals_interactive();
	while (1)
	{
		command = readline("minishell$ ");
		if (command == NULL)
			exit(EXIT_FAILURE);
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
