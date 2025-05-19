#include "minishell.h"

bool	check_arg_export_syntax(char *arg);
char	*remove_extra_char_before_egal(char *arg);
bool	error_export(char *arg);
void	export_all(char **envp);
void	export_arg_to_env(t_shell *shell, char *arg);

int	ft_export(t_shell *shell)
{
	size_t	i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (shell->cmd->cmd[i] == 0)
		export_all(shell->envp);
	while (shell->cmd->cmd[i])
	{
		if (check_arg_export_syntax(shell->cmd->cmd[i]) == true)
			export_arg_to_env(shell, shell->cmd->cmd[i]);
		else
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

void	export_arg_to_env(t_shell *shell, char *arg)
{
	t_envp	*new_envp;
	t_envp	*env;
	char	**tmp;
	char	*new_arg;

	env = NULL;
	new_arg = remove_extra_char_before_egal(arg);
	new_envp = create_node_envp(new_arg);
	env = fill_envp(env, shell->envp);
	ft_add_back_envp(&env, new_envp);
	tmp = shell->envp;
	shell->envp = ft_convert_node_to_envp(env);
	free(tmp);
	free(env);
	free(new_arg);
}

char	*remove_char_arg(char *arg)
{
	char	*new_arg;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	new_arg = malloc(sizeof(char) * (ft_strlen(arg)));
	if (!new_arg)
		return (NULL);
	while (arg[i] != '=')
		i++;
	ft_memmove(new_arg, arg, i - 1);
	ft_memmove(new_arg + i - 1, arg + i, ft_strlen(arg) - i);
	new_arg[ft_strlen(arg) - 1] = '\0';
	return (new_arg);
}

char	*remove_extra_char_before_egal(char *arg)
{
	size_t	i;
	bool	remove_char;

	i = 0;
	remove_char = false;
	while (arg[i] != '\0')
	{
		if (arg[i + 1] == '=' && (arg[i] == '+'
			|| arg[i] == '_' || arg[i] == '<' || arg[i] == '>'))
			remove_char = true;
		i++;
	}
	if (remove_char == true)
		return (remove_char_arg(arg));
	return (ft_strdup(arg));
}

bool	check_arg_export_syntax(char *arg)
{
	size_t	i;

	i = 1;
	if (arg[0] == '-' && arg[1] != '\0')
	{
		printf("bash: export: %c%c: invalid option\n", arg[0], arg[1]);
		printf("export: usage:export [name[=value] ...]");
		return (false);
	}
	if (ft_isalpha(arg[0]) != true)
		return (error_export(arg));
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		else if (ft_isalnum(arg[i]) != true && arg[i + 1] != '=')
			return (error_export(arg));
		else if (ft_isalnum(arg[i]) != 1 && arg[i + 1] == '=' && arg[i] != '+'
					&& arg[i] != '_' && arg[i] != '<' && arg[i] != '>')
			return (error_export(arg));
		i++;
	}
	return (true);
}

bool	error_export(char *arg)
{
	printf("export: `%s': not a valid identifier", arg);
	return (false);
}

void	export_all(char **envp)
{
	size_t	i;
	size_t	k;

	i = 0;
	while (envp[i])
	{
		k = 0;
		ft_putstr_fd("export ", 1);
		while (envp[i][k])
		{
			if (k > 0)
				if (envp[i][k - 1] == '=')
					ft_putchar_fd('"', 1);
			ft_putchar_fd(envp[i][k], 1);
			k++;
		}
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}
