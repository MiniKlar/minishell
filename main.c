#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell *shell;
	char *command;

	shell = init_shell(envp);
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
	}
	return (shell->wstatus);
}
