#include <minishell.h>

bool	is_cmd_built_ins(t_token *tokens, char **envp)
{
	char *buffer;
	buffer = NULL;
	if (ft_strncmp(tokens->tokens, "export", 5) == 0)
	{
		export(tokens, envp);
		return (true);
	}
	else if (ft_strncmp(tokens->tokens, "pwd", 3) == 0)
	{
		buffer = pwd(true);
		free(buffer);
		return (true);
	}
	else if (ft_strncmp(tokens->tokens, "cd", 2) == 0)
	{
		cd(tokens, envp);
		return (true);
	}
	else if ((ft_strncmp(tokens->tokens, "echo ", 5) == 0))
	{
		//ft_echo(tab_cmd, node);
		return (true);
	}
	else if (ft_strncmp(tokens->tokens, "exit", 4) == 0)
	{
		ft_exit(tokens);
		return (true);
	}
	else if (ft_strncmp(tokens->tokens, "env", 3) == 0)
	{
		env(envp);
		return (true);
	}
	return (false);
}

bool exec_shell_param(t_token *tokens, char **envp)
{
	if (is_shell_parameter(tokens) == false)
		return (false);
	else
		append_envp(tokens, envp);
	return (true);
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
		char *arg[] = { NULL };
		id_fork = fork();
		if (id_fork == 0)
		{
			if (execve(tokens->tokens, arg, envp) == -1)
			{
				perror(tokens->tokens);
				free_tokens(tokens);
				exit(127);
			}
		}
		else
		{
			waitpid(id_fork, 0, 0);
			printf("COMMAND EXECUTED SUCCESSFULLY\n");
		}
	}
}
