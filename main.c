#include "minishell.h"

int main(int argc, char **argv, char** envp)
{
	char *command;
	char **tab_cmd;
	//char *buffer;
	t_params *node = NULL;
	bool shell_on = true;
	(void)argc;
	(void)argv;
	while (shell_on)
	{
		t_token *tokens = NULL;
		command = readline("minishell exec test$ ");
		if (command == NULL)
			exit(EXIT_FAILURE);
		tab_cmd = ft_split(command, ' ');
		tokens = fill_token(tokens, tab_cmd);
		free_tab(tab_cmd);
		print_tokens(tokens);
		printf("nbr of pipes: %zu\n", print_pipes_nbr(tokens));
		if (strncmp(command, "exit", 3) == 0)
		{
			ft_exit(node);
			shell_on = false;
		}
		else
		{
			ft_pipe(tokens, envp);
		// if (strncmp(command, "pwd", 3) == 0)
		// {
		// 	buffer = pwd(true);
		// 	free(buffer);
		// }
		// else if (strncmp(command, "cd", 2) == 0)
		// 	cd("..");
		// else if ((strncmp(command, "echo ", 5) == 0))
		// 	ft_echo(tab_cmd, node);

		// else if (is_shell_parameter(command))
		// 	node = add_parameters(command, node);
		if (strncmp(command, "", 1) != 0)
			add_history(command);
		}
		free_tokens(tokens);
	}
	return (EXIT_SUCCESS);
}
