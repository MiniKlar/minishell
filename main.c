#include "minishell.h"

int main(void)
{
	t_shell *shell;
	char *command;

	shell = init_shell(environ);
	set_signals_interactive(); //ajoutee pour signaux
	while (1)
	{
		command = readline("bash-5.1$ ");
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
