#include "minishell.h"

bool	error_infile(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (false);
}

bool	redir_infile(t_shell *shell)
{
	int		fd;
	char	*str;

	str = shell->cmd->redir->str;
	if (access(str, F_OK) != 0)
		return(error_infile(str), false);
	else if (access(str, R_OK) != 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (false);
	}
	fd = open(str, O_RDWR);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Cannot open file\n", 2);
		return (false);
	}
	if (shell->cmd->fd_in > -1)
		close(shell->cmd->fd_in);
	shell->cmd->fd_in = fd;
	return (true);
}
