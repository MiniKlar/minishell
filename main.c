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
		t_token *tokens = NULL;
		command = readline("bash-5.1$ ");
		if (command == NULL)
			exit(EXIT_FAILURE);
		tab_cmd = ft_split(command, ' ');
		tokens = fill_token(tokens, tab_cmd);
		free_tab(tab_cmd);
		exec_cmd(tokens, envp);
		if (ft_strncmp(command, "", 1) != 0)
			add_history(command);
		free_tokens(tokens);
		free(command);
	}
	return (EXIT_SUCCESS);
}
