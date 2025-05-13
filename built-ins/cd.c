#include "minishell.h"

char *get_prev_pwd(char **envp);

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

int cd(t_shell *shell, char **envp)
{
	char *arg;
	size_t	i;

	i = 0;
	if (shell->next == NULL)
	{
		arg = get_specific_env(envp, "HOME");
		return (exec_cd(arg));
	}
	if (check_arg_nbr(shell) == -1)
		return (1);
	arg = get_cd_argument(shell->next, envp);
	if (arg == NULL)
		return (1);
	else
		return (exec_cd(arg));
}
