#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *command;
	char **tab_cmd;
	//char *buffer;
	//t_tmp_env *node = NULL;
	(void)argc;
	(void)argv;
	while (1)
	{
		t_shell *shell = NULL;
		command = readline("bash-5.1$ ");
		if (command == NULL)
			exit(EXIT_FAILURE);
		tab_cmd = ft_split(command, ' ');
		shell = fill_token(shell, tab_cmd);
		free_tab(tab_cmd);
		exec(shell, &envp);
		if (ft_strncmp(command, "", 1) != 0)
			add_history(command);
		free_shell(shell);
		free(command);
	}
	return (EXIT_SUCCESS);
}
