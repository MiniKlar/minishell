#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

int	main(void)
{
	t_shell	*shell;

	shell = init_shell(environ);
	while (1)
	{
		set_signals_interactive();
		shell->readline_cmd = readline("minishell$ ");
		if (shell->readline_cmd == NULL)
		{
			free_eof(shell);
			exit(0);
		}
		if (parsing(shell, shell->readline_cmd) == true)
		{
			exec(shell);
			free_shell(shell);
		}
		if (ft_strncmp(shell->readline_cmd, "", 1) != 0)
			add_history(shell->readline_cmd);
		if (shell->readline_cmd)
		{
			free(shell->readline_cmd);
			shell->readline_cmd = NULL;
		}
		environ = shell->envp;
	}
	return (shell->exit_code);
}
