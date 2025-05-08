#include <minishell.h>

void append_envp(t_token *tokens, char **envp)
{
	t_envp *env;
	t_envp *new_node;

	env = NULL;
	env = fill_envp(env, envp);
	new_node = create_node_envp(tokens->tokens);
	ft_add_back_envp(&env, new_node);
	while (env)
	{
		printf("ENVP = %s\n", env->envp);
		env = env->next;
	}
}

bool exec_shell_param(t_token *tokens, char **envp)
{
	if (is_shell_parameter(tokens) == false)
		return (false);
	else
		append_envp(tokens, envp);
	return (true);
}

bool	is_cmd_built_ins(t_token *tokens, char **envp)
{
	char *buffer;
	(void)envp;
	buffer = NULL;
	if (ft_strncmp(tokens->tokens, "pwd", 3) == 0)
	{
		buffer = pwd(true);
		free(buffer);
		return (true);
	}
	else if (ft_strncmp(tokens->tokens, "cd", 2) == 0)
	{
		cd("..");
		return (true);
	}
	// else if ((ft_strncmp(tokens->tokens, "echo ", 5) == 0))
	// {
	// 	ft_echo(tab_cmd, node);
	// 	return (true);
	// }
	else if (ft_strncmp(tokens->tokens, "exit", 4) == 0)
	{
		ft_exit(tokens);
		return (true);
	}
	return (false);
}

void exec_cmd(t_token *tokens, char **envp)
{
	if (is_cmd_built_ins(tokens, envp) == true)
		printf("Built-ins executed\n");
	else if (exec_shell_param(tokens, envp) == true)
		printf("Shell parameters added to envp\n");
	else
	{
		pid_t id_fork;

		id_fork = fork();
		if (id_fork == 0)
		{
			if (execve(tokens->tokens, &tokens->tokens, envp) == -1)
			{
				free_tokens(tokens);
				exit(127);
			}
		}
		else
		{
			printf("COMMAND EXECUTED SUCCESSFULLY\n");
		}
	}
}
