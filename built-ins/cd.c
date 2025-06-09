#include "minishell.h"

int		check_arg_nbr(t_shell *shell);
void	update_pwd(t_shell *shell);

int	exec_cd(t_shell *shell, char *arg)
{
	if (chdir(arg) == -1)
	{
		perror("cd");
		free(arg);
		return (1);
	}
	else
	{
		update_pwd(shell);
		free(arg);
		return (0);
	}
}

char	*handle_specific_case(char *directory)
{
	char	*arg;

	arg = NULL;
	if (directory == NULL)
		arg = getenv("PWD=");
	else if (ft_strncmp(directory, ".", 2) == 0)
		arg = getenv("PWD=");
	else if (ft_strncmp(directory, "..", 3) == 0)
		arg = ft_strdup("..");
	else if (ft_strncmp(directory, "~", 2) == 0)
		arg = getenv("HOME=");
	else if (ft_strncmp(directory, "-", 2) == 0)
		arg = getenv("OLDPWD=");
	return (arg);
}

int ft_cd(t_shell *shell)
{
	char	*arg;
	char	*directory;

	directory = shell->cmd->cmd[1];
	if (check_arg_nbr(shell) == -1)
		return (1);
	arg = handle_specific_case(directory);
	if (arg != NULL)
		return (exec_cd(shell, arg));
	else
		return (exec_cd(shell, ft_strdup(directory)));
}

void	update_pwd(t_shell *shell)
{
	t_envp	*env;
	char	*new_pwd;
	char	*new_env;

	env = NULL;
	env = fill_envp(env, shell->envp);
	new_pwd = getcwd(NULL, 0);
	new_env = ft_strjoin("OLDPWD=", getenv("PWD"));
	if (!find_change_env(env, new_env, "OLDPWD="))
	{
		ft_add_back_envp(&env, create_node_envp(new_env));
		free(new_env);
	}
	find_change_env(env, ft_strjoin("PWD=", new_pwd), "PWD=");
	free_array(shell->envp);
	shell->envp = ft_convert_node_to_envp(env);
	free_env(env);
	free(new_pwd);
}

int	check_arg_nbr(t_shell *shell)
{
	size_t i;

	i = 0;
	while (shell->cmd->cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return (-1);
	}
	else
		return (0);
}
