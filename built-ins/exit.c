#include "minishell.h"

static bool	check_if_int_out_of_range(char *cmd)
{
	long long 	nbr;
	char		*str;
	size_t		i;

	i = 0;
	nbr = atoll(cmd);
	if (nbr != 0)
	{
		str = ft_itoa(nbr);
		printf("voici str = %s\n", str);
		while (str && cmd)
		{
			if (str[i] == cmd[i])
				i++;
			else
				return (true);
		}
	}
	if (str[i] == '\0' && cmd[i] != '\0')
		return (true);
	else
		return (false);
}

static void	exit_status_free(t_shell *shell, int code)
{
	free_array(shell->envp);
	free_all(shell);
	free(shell);
	clear_history();
	exit(code);
}

static void	print_error(t_shell *shell, char *cmd, int error, int *code)
{
	if (error == 0)
	{
		if (cmd)
		{
			ft_putstr_fd("bash: exit", 2);
			ft_putstr_fd(": too many arguments\n", 2);
			exit_status_free(shell, 1);
		}
	}
	else if (error == 1)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*code = 255;
		exit_status_free(shell, *code);
	}
}

static void	check_if_number(char *cmd, int *is_number)
{
	size_t	i;

	i = 0;
	*is_number = 0;
	if (cmd)
	{
		while (cmd[i] != '\0')
		{
			if (i == 0)
			{
				if (cmd[i] == '+' || cmd[i] == '-')
					i++;
			}
			if (ft_isdigit(cmd[i]) == 1)
				*is_number = 1;
			else
			{
				*is_number = 2;
				break;
			}
			i++;
		}
	}
}

void	ft_exit(t_shell *shell)
{
	int	code;
	int is_number;
	ft_putstr_fd("exit\n", 1);
	check_if_number(shell->cmd->cmd[1], &is_number);
	if (is_number == 1)
		shell->wstatus = atoi(shell->cmd->cmd[1]);
	if (shell->wstatus == -1)
	{
		if (check_if_int_out_of_range(shell->cmd->cmd[1]) == true)
			print_error(shell, shell->cmd->cmd[1], 1, &code);
	}
	printf("Voici wstatus = %d\n", shell->wstatus);
	code = shell->wstatus;
	if (is_number == 2)
		print_error(shell, shell->cmd->cmd[1], 1, &code);
	else
	{
		if (shell->cmd->cmd[1] != 0)
		{
			print_error(shell, shell->cmd->cmd[2], 0, &code);
			if (shell->cmd->cmd[1][0] == '-' && is_number == 1)
				code = 256 + shell->wstatus;
		}
	}
	exit_status_free(shell, code);
}
