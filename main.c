#include "minishell.h"

int main(void)
{
	t_shell *shell;
	char *command;

	shell = init_shell(environ);
	get_shell_context(shell);
	set_signals_interactive(); //ajoutee pour signaux
	while (1)
	{
		command = readline("bash-5.1$ ");
		if (command == NULL)
		{
			free_all(shell);
			free_array(shell->envp);
			free(shell);
			write(STDOUT_FILENO, "exit\n", 5);
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
