#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

void	print_command(t_cmd *cmd, int index)
{
	printf("Commande %d:\n", index);
	if (cmd->cmd)
	{
		for (int j = 0; cmd->cmd[j]; j++)
			printf("  arg[%d] = %s\n", j, cmd->cmd[j]);
	}
	else
		printf("  (no arguments)\n");
}

void	print_redirections(t_redir *redir, int cmd_index)
{
	const char	*symbols[] = {"IN", "OUT", "HEREDOC", "APPEND"};
	int			i = 0;

	if (!redir) return;

	printf("Redirections pour commande %d:\n", cmd_index);
	while (redir)
	{
		printf("  [%s] -> %s\n", symbols[redir->symbol], redir->str);
		redir = redir->next;
		i++;
	}
}

void	print_shell(t_shell *shell)
{
	t_cmd	*current_cmd;
	int		i;

	current_cmd = shell->cmd;
	i = 0;
	printf("\n====== RESULTAT PARSING ======\n");
	printf("Pipes: %zu\n", shell->nb_pipe);

	while (current_cmd)
	{
		printf("\n=== COMMANDE %d ===\n", i);
		print_command(current_cmd, i);
		print_redirections(current_cmd->redir, i);
		current_cmd = current_cmd->next;
		i++;
	}
	printf("\n==============================\n\n");
}

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
			while (shell->cmd != NULL)
			{
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
