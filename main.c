#include "minishell.h"

t_shell *init_test_struct(t_shell *shell);
t_cmd *create_node_cmd(void);
t_cmd *create_node_cmd2(void);
t_cmd *create_node_cmd3(void);
t_cmd *create_node_cmd4(void);
t_cmd *create_node_cmd5(void);
t_cmd *create_node_cmd6(void);
t_cmd *create_node_cmd7(void);
t_cmd *create_node_cmd8(void);
t_cmd *create_node_cmd9(void);
t_cmd *create_node_cmd10(void);
t_cmd *create_node_cmd11(void);
t_cmd *create_node_cmd12(void);
t_cmd *create_node_cmd13(void);
t_cmd *create_node_cmd14(void);
t_cmd *create_node_cmd15(void);
t_cmd *create_node_cmd16(void);
t_cmd *create_node_cmd17(void);
t_cmd *create_node_cmd18(void);
t_cmd *create_node_cmd19(void);
t_cmd *create_node_cmd20(void);
t_cmd *create_node_cmd21(void);
t_cmd *create_node_cmd22(void);
t_cmd *create_node_cmd23(void);
t_cmd *create_node_cmd24(void);
t_cmd *create_node_cmd25(void);
t_cmd *create_node_cmd26(void);
t_cmd *create_node_cmd27(void);
t_cmd *create_node_cmd28(void);


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
		shell->cmd->next->next = create_node_cmd3();
		shell->cmd->next->next->next = create_node_cmd5();
		shell->cmd->next->next->next->next = create_node_cmd6();
		shell->cmd->next->next->next->next->next = create_node_cmd7();
		shell->cmd->next->next->next->next->next->next = create_node_cmd8();
		shell->cmd->next->next->next->next->next->next->next = create_node_cmd9();
		shell->cmd->next->next->next->next->next->next->next->next = create_node_cmd10();
		shell->cmd->next->next->next->next->next->next->next->next->next = create_node_cmd11();
		shell->cmd->next->next->next->next->next->next->next->next->next->next = create_node_cmd12();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd13();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd14();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd15();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd16();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd17();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd18();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd19();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd20();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd21();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd22();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd23();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd24();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd25();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd26();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd27();
		shell->cmd->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = create_node_cmd28();
		shell->wstatus = 0;
		shell->fd_in = STDIN_FILENO;
		shell->fd_out = STDOUT_FILENO;
		shell->nb_pipe = 26;
		exec(shell);
		if (ft_strncmp(command, "", 1) != 0)
			add_history(command);
		envp = shell->envp;
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

	char *str ="ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd2(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd3(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd4(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}
t_cmd *create_node_cmd5(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd6(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd7(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd8(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd9(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd10(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd11(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd12(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd13(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd14(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd15(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd16(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd17(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd18(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd19(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd20(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd21(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd22(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd23(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd24(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd25(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd26(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd *create_node_cmd27(void)
{
	t_cmd	*cmd;

	char *str = "ls";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}
t_cmd *create_node_cmd28(void)
{
	t_cmd	*cmd;

	char *str = "grep LI";
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_split(str, ' ');
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}
