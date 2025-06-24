#include "minishell.h"

bool	error_infile(char *str)
{
	perror("File not accessible");
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (false);
}

bool	redir_infile(t_shell *shell)
{
	int		fd;
	char	*str;

	str = shell->cmd->redir->str;
	if (access(str, F_OK) != 0)
		error_infile(str);
	else if (access(str, R_OK) != 0)
	{
		perror("File not readable");
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	fd = open(str, O_RDWR);
	if (fd == -1)
	{
		perror("Cannot open file");
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	if (shell->cmd->fd_in > -1)
		close(shell->cmd->fd_in);
	shell->cmd->fd_in = fd;
	return (true);
}
