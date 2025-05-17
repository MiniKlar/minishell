#include "minishell.h"

char	*get_prev_pwd(char **envp);
char	*join_args(char *arg, char *new_arg);
char	*check_arg(char *arg, char **envp);
char	*get_cd_argument(char *cmd, char **envp);
char	*get_specific_env(char **envp, char *env);
char	*get_prev_pwd(char **envp);
int		check_arg_nbr(t_shell *shell);
void	update_pwd(t_shell *shell, char *arg);

int	exec_cd(char *arg)
{
	if (chdir(arg) == -1)
	{
		perror("cd");
		return (1);
	}
	else
	{
		printf("Success! You changed the directory\n");
		return (0);
	}
}

int ft_cd(t_shell *shell)
{
	char *arg;
	size_t	i;

	i = 0;
	if (shell->cmd->cmd[1] == NULL)
	{
		arg = get_specific_env(shell->envp, "HOME");
		return (exec_cd(arg));
	}
	if (check_arg_nbr(shell) == -1)
		return (1);
	arg = get_cd_argument(shell->cmd->cmd[1], shell->envp);
	if (arg == NULL)
		return (1);
	else
	{
		exec_cd(arg);
		if (ft_strncmp(shell->cmd->cmd[1], "-\0", 2) == 0)
			ft_pwd(shell, true);
		update_pwd(shell, arg);
		return (0);
	}
}

void	find_change_env(t_envp *env, char *new_env, char *env_to_replace)
{
	while (env)
	{
		if (ft_strncmp(env->envp, env_to_replace, ft_strlen(env_to_replace)) == 0)
		{
			env->envp = new_env;
			break ;
		}
		env = env->next;
	}
}

char	**ft_convert_node_to_envp(t_envp *env)
{
	char *tmp;
	char *envp;
	char **final_envp;

	envp = NULL;
	if (!envp)
		envp = ft_strdup("");
	if (!envp)
		return (NULL);
	while (env)
	{
		tmp = envp;
		envp = ft_strjoin(envp, env->envp);
		free(tmp);
		tmp = envp;
		envp = ft_strjoin(envp, " ");
		free(tmp);
		env = env->next;
	}
	final_envp = ft_split(envp, ' ');
	free(envp);
	return(final_envp);
}

void	update_pwd(t_shell *shell, char *arg)
{
	char *oldpwd;
	char *oldpwd_tmp;
	char *new_env;
	char **tmp;
	t_envp	*env;

	env = NULL;
	oldpwd_tmp = get_specific_env(shell->envp, "PWD=");
	oldpwd = ft_substr(oldpwd_tmp, 0, ft_strlen(oldpwd_tmp));
	free(oldpwd_tmp);
	oldpwd_tmp = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	new_env = ft_strjoin("PWD=", arg);
	env = fill_envp(env, shell->envp);
	find_change_env(env, new_env, "PWD");
	find_change_env(env, oldpwd_tmp, "OLDPWD");
	tmp = shell->envp;
	shell->envp = ft_convert_node_to_envp(env);
	free(new_env);
	free(tmp);
}

char *join_args(char *arg, char *new_arg)
{
	char *tmp;

	if (!new_arg)
		new_arg = ft_strdup("");
	if (!new_arg)
		return (NULL);
	tmp = new_arg;
	new_arg = ft_strjoin(new_arg, arg);
	free(tmp);
	tmp = new_arg;
	new_arg = ft_strjoin(new_arg, "/");
	free(tmp);
	free(arg);
	return (new_arg);
}

char *check_arg(char *arg, char **envp)
{
	if (ft_strncmp(arg, ".", 2) == 0)
		arg = get_specific_env(envp, "PWD=");
	else if (ft_strncmp(arg, "..", 3) == 0)
		arg = get_prev_pwd(envp);
	else if (ft_strncmp(arg, "~", 2) == 0)
		arg = get_specific_env(envp, "HOME=");
	else if (ft_strncmp(arg, "-", 2) == 0)
		arg = get_specific_env(envp, "OLDPWD=");
	return (arg);
}

char	*get_cd_argument(char *cmd, char **envp)
{
	size_t	i;
	char *arg;
	char *new_arg;
	char **arg_tab;

	i = 0;
	if (ft_strchr(cmd, '/') != NULL)
	{
		arg_tab = ft_split(cmd, '/');
		while (arg_tab[i])
		{
			arg = check_arg(arg_tab[i], envp);
			new_arg = join_args(arg, new_arg);
			i++;
		}
		free_tab(arg_tab);
	}
	else
	{
		arg_tab = NULL;
		new_arg = check_arg(cmd, envp);
	}
	return (new_arg);
}

int	check_arg_nbr(t_shell *shell)
{
	size_t i;

	i = 0;
	while (shell->cmd->cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments", 2);
		return (-1);
	}
	else
		return (0);
}

char *get_specific_env(char **envp, char *env)
{
	size_t	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, ft_strlen(env)) == 0)
			return (ft_substr(envp[i], ft_strlen(env), ft_strlen(envp[i]) - ft_strlen(env)));
		i++;
	}
	return (NULL);
}

char *get_prev_pwd(char **envp)
{
	size_t	i;
	char	*current_pwd;

	current_pwd = get_specific_env(envp, "PWD");
	if (ft_strncmp(current_pwd, "/home\0", ft_strlen(current_pwd)) == 0)
		return (ft_strdup("/"));
	i = ft_strlen(current_pwd);
	while (current_pwd[i] != '/')
		i--;
	return (ft_substr(current_pwd, 0, i));
}


