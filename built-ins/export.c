#include "minishell.h"

char **ft_transform_envp(t_envp *env)
{
	char **envp;
	char *tmp_env;
	char *tmp;

	tmp_env = ft_strdup("");
	if (!tmp_env)
		return (NULL);
	while (env)
	{
		tmp = tmp_env;
		tmp_env = ft_strjoin(tmp_env, env->envp);
		free(tmp);
		if (env->next != NULL)
		{
			tmp = tmp_env;
			tmp_env = ft_strjoin(tmp_env, " ");
			free(tmp);
		}
		env = env->next;
	}
	envp = ft_split(tmp_env, ' ');
	free(tmp_env);
	free_env(env);
	return (envp);
}

t_envp *append_envp(char *arg, char **envp)
{
	t_envp *env;
	t_envp *new_node;

	env = NULL;
	env = fill_envp(env, envp);
	new_node = create_node_envp(arg);
	ft_add_back_envp(&env, new_node);
	return (env);
}

bool is_shell_parameter(t_shell *shell)
{
	char *arg;
	size_t	i;

	i = 0;
	if (shell->next == NULL)
		return (false);
	shell = shell->next;
	arg = shell->cmd[0];
	while (arg[i])
	{
		if (ft_isalpha(arg[i]) != 1 && arg[i] != '=') //faire en sorte que le premier soit check si cest pas un nombre et apres nombre ok
			return (false);
		if (arg[i] == '=')
			return (true);
		i++;
	}
	return(false);
}

void	export(t_shell *shell, char **envp)
{
	t_envp *env;
	char *arg;

	if (is_shell_parameter(shell) == false)
		;
	else
	{
		shell = shell->next;
		arg = shell->cmd[0];
		env = append_envp(arg, envp);
		envp = ft_transform_envp(env);
	}
}
