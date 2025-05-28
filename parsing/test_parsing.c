#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

int	main(void)
{
	t_shell	*shell;
	char	*line;
	int		i;
	shell = init_shell();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		shell = parsing(shell, line);
		if (shell)
		{
			printf("VOICI LE NOMBRE DE PIPES = %zu\n", shell->nb_pipe);
			while (shell->cmd != NULL)
			{
				if (shell->cmd->redir != NULL)
				while (shell->cmd->redir)
				{
					printf("VOICI REDIR STR = %s\n", shell->cmd->redir->str);
					shell->cmd->redir = shell->cmd->redir->next;
				}
				i = 0;
				while (shell->cmd->cmd[i] != 0)
				{
					printf("COMMAND[%d] = %s\n", i, shell->cmd->cmd[i]);
					i++;
				}
				shell->cmd = shell->cmd->next;
			}
		}
		free_shell(shell);
		free(line);
	}
	printf("exit\n");
	return (0);
}
