#include "minishell.h"

int main(void)
{
<<<<<<< Updated upstream
	t_shell *shell;
	char *command;
=======
	free_all(shell);
	free_array(shell->envp);
	free(shell);
	write(STDOUT_FILENO, "exit\n", 5);
}

int	main(void)
{
	t_shell	*shell;
>>>>>>> Stashed changes

	shell = init_shell(environ);
	get_shell_context(shell);
	set_signals_interactive(); //ajoutee pour signaux
	while (1)
	{
<<<<<<< Updated upstream
		command = readline("bash-5.1$ ");
		if (command == NULL)
=======
		shell->readline_cmd = readline("minishell$ ");
		if (shell->readline_cmd == NULL)
>>>>>>> Stashed changes
		{
			free_all(shell);
			free_array(shell->envp);
			free(shell);
			write(STDOUT_FILENO, "exit\n", 5);
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
