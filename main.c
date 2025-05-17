#include "minishell.h"

t_shell *init_test_struct(t_shell *shell);
t_cmd *create_node_cmd(void);
t_cmd *create_node_cmd2(void);
// t_cmd *create_node_cmd3(void);
// t_cmd *create_node_cmd4(void);

int main(int argc, char **argv, char **envp)
{
	char *command;
	(void)argc;
	(void)argv;
	t_shell *shell = NULL;
	shell = init_test_struct(shell);
	shell->envp = ft_malloc_envp(envp);
	while (1)
	{
		command = readline("bash-5.1$ ");
		if (command == NULL)
			exit(EXIT_FAILURE);
		shell->cmd = create_node_cmd();
		shell->cmd->next = create_node_cmd2();
		// shell->cmd->next->next = create_node_cmd3();
		// shell->cmd->next->next->next = create_node_cmd4();
		shell->wstatus = 0;
		shell->fd_in = STDIN_FILENO;
		shell->fd_out = STDOUT_FILENO;
		shell->nb_pipe = 1;
		shell->redir = NULL;
		exec(shell);
		if (ft_strncmp(command, "", 1) != 0)
			add_history(command);
		envp = shell->envp;
		free_shell(shell);
		free(command);
	}
	return (EXIT_SUCCESS);
}

t_shell *init_test_struct(t_shell *shell)
{
	int	i;

	i = 0;
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (NULL);
	return (shell);
}

t_cmd *create_node_cmd(void)
{
	t_cmd	*cmd;

	char *str ="export";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd2(void)
{
	t_cmd	*cmd;

	char *str = "echo hola";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->next = NULL;
	return (cmd);
}

// t_cmd *create_node_cmd3(void)
// {
// 	t_cmd	*cmd;

// 	char *str = "echo hola";
// 	cmd = malloc(sizeof(*cmd));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->cmd = ft_split(str, ' ');
// 	cmd->next = NULL;
// 	return (cmd);
// }

// t_cmd *create_node_cmd4(void)
// {
// 	t_cmd	*cmd;

// 	char *str = "rev";
// 	cmd = malloc(sizeof(*cmd));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->cmd = ft_split(str, ' ');
// 	cmd->next = NULL;
// 	return (cmd);
// }
