#include "minishell.h"

t_shell *init_test_struct(t_shell *shell);

int main(int argc, char **argv, char **envp)
{
	char *command;
	// char **tab_cmd;
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
		// tab_cmd = ft_split(command, ' ');
		// shell = fill_token(shell, tab_cmd);
		// free_tab(tab_cmd);
		shell = init_test_struct(shell);
		exec(shell, envp);
		if (ft_strncmp(command, "", 1) != 0)
			add_history(command);
		free_shell(shell);
		free(command);
	}
	return (EXIT_SUCCESS);
}

t_shell *init_test_struct(t_shell *shell)
{
	int	i;
	t_redir *redir;
	t_redir *redir2;
	t_redir *redir3;
	t_redir *redir4;
	t_redir *redir5;

	i = 0;
	redir = create_node_here_redir("caca");
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (NULL);
	shell->cmd = malloc(sizeof(char *) * (2));
	shell->cmd[0] = ft_strdup("/usr/bin/cat");
	// shell->cmd[1] = ft_strdup("Makefile");
	shell->cmd[1] = 0;
	shell->hdc_idx = 0;
	shell->nb_pipe = 0;
	shell->wstatus = 0;
	shell->fd_in = 0;
	shell->fd_out = 1;
	shell->next = NULL;
	shell->redir = redir;
	redir2 = create_node_redir_out("outfile");
	shell->redir->next = redir2;
	redir3 = create_node_redir("infile_2");
	shell->redir->next->next = redir3;
	redir4 = create_node_here_redir("prout");
	shell->redir->next->next->next = redir4;
	redir5 = create_node_redir("infile");
	shell->redir->next->next->next->next = redir5;
	return (shell);
}
