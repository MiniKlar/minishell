#include "minishell.h"

int main(void)
{
	char *command;
	char **tab_cmd;
	char *buffer;
	bool shell_on = true;


	while (shell_on)
	{
		command = readline("minishell exec test$ ");
		if (command == NULL)
			return (EXIT_FAILURE);
		tab_cmd = ft_split(command, ' ');
		if (strncmp(command, "pwd", 3) == 0)
		{
			buffer = pwd(true);
			free(buffer);
		}
		else if (strncmp(command, "cd", 2) == 0)
			cd("..");
		else if ((strncmp(command, "echo", 4) == 0))
			ft_echo(tab_cmd);
		else if (strncmp(command, "exit", 3) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			shell_on = false;
		}
		if (strncmp(command, "", 1) != 0)
			add_history(command);
		free_tab(tab_cmd);
	}
	return (EXIT_SUCCESS);
}
