#include "minishell.h"

t_shell *init_test_struct(t_shell *shell);
t_cmd *create_node_cmd(void);

int main(int argc, char **argv, char **envp)
{
	char *command;
	// char **tab_cmd;
	//char *buffer;
	//t_tmp_env *node = NULL;
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
		shell->wstatus = 0;
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
	// t_redir *redir;
	// t_redir *redir2;
	// t_redir *redir3;
	// t_redir *redir4;
	// t_redir *redir5;

	i = 0;
	// redir = create_node_here_redir("caca");
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (NULL);
	// shell->hdc_idx = 0;
	// shell->nb_pipe = 0;
	// shell->fd_in = 0;
	// shell->fd_out = 1;
	// redir2 = create_node_redir_out("outfile");
	// shell->redir->next = redir2;
	// redir3 = create_node_redir("infile_2");
	// shell->redir->next->next = redir3;
	// redir4 = create_node_here_redir("prout");
	// shell->redir->next->next->next = redir4;
	// redir5 = create_node_redir("infile");
	// shell->redir->next->next->next->next = redir5;
	return (shell);
}

t_cmd *create_node_cmd(void)
{
	t_cmd	*cmd;

	char *str = "echo -n caca prout pipi albillie bombe a chiotte";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->next = NULL;
	return (cmd);
}
