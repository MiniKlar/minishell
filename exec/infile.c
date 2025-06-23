#include "minishell.h"

bool	redir_infile(t_shell *shell)
{
	int		fd;
	char	*str;

	str = shell->cmd->redir->str;
	if (access(str, F_OK) != 0)
	{
		perror("File not accessible");
		return (false);
	}
	else if (access(str, R_OK) != 0)
	{
		perror("File not readable");
		return (false);
	}
	fd = open(str, O_RDWR);
	if (fd == -1)
	{
		perror("Cannot open file");
		return (false);
	}
	if (shell->fd_in > -1)
		close(shell->fd_in);
	shell->fd_in = fd;
	return (true);
}
