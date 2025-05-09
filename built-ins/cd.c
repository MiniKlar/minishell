#include "minishell.h"

char *get_prev_pwd(char **envp);

char *get_specific_env(char **envp, char *env)
{
	size_t	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, ft_strlen(env)) == 0)
			return (ft_substr(envp[i], ft_strlen(env) + 1, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (NULL);
}

int	check_arg_nbr(t_token *tokens)
{
	size_t i;

	i = 0;
	while (tokens)
	{
		tokens = tokens->next;
		i++;
	}
	if (i > 2)
		return (-1);
	else
		return (0);
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
	if (ft_strncmp(arg, ".", 1) == 0 && arg[1] == '\0')
		arg = get_specific_env(envp, "PWD");
	else if (ft_strncmp(arg, "..", 2) == 0 && (arg[2] == '\0'))
		arg = get_prev_pwd(envp);
	else if (ft_strncmp(arg, "~", 1) == 0 && (arg[1] == '\0'))
		arg = get_specific_env(envp, "HOME");
	return (ft_strdup(arg));
}

char	*get_cd_argument(t_token *tokens, char **envp)
{
	size_t	i;
	char *arg;
	char *new_arg;
	char **arg_tab;

	i = 0;
	arg = tokens->tokens;
	if (ft_strchr(arg, '/') != NULL)
	{
		arg_tab = ft_split(arg, '/');
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
		new_arg = check_arg(arg, envp);
	}
	return (new_arg);
}

char *get_prev_pwd(char **envp)
{
	size_t	i;
	char	*current_pwd;

	current_pwd = get_specific_env(envp, "PWD");
	i = ft_strlen(current_pwd);
	while (current_pwd[i] != '/')
		i--;
	return (ft_substr(current_pwd, 0, i - 1));
}

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

int cd(t_token *tokens, char **envp)
{
	char *arg;
	size_t	i;

	i = 0;
	if (tokens->next == NULL)
	{
		arg = get_specific_env(envp, "HOME");
		return (exec_cd(arg));
	}
	if (check_arg_nbr(tokens) == -1)
		return (1);
	arg = get_cd_argument(tokens->next, envp);
	if (arg == NULL)
		return (1);
	else
		return (exec_cd(arg));
}
