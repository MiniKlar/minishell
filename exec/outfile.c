#include "minishell.h"

bool	redir_outfile(t_shell *shell)
{
	int	fd;
	char *str;

	str = shell->cmd->redir->str;
	if (shell->cmd->redir->symbol == APPEND)
		fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0755);
	else
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd == -1)
	{
		perror("Cannot open file");
		return (false);
	}
	if (shell->fd_out > -1)
		close(shell->fd_out);
	shell->fd_out = fd;
	return (true);
}
