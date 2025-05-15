#include "minishell.h"

void	redir_outfile(t_shell *shell)
{
	int	fd;
	char *str;

	str = shell->redir->str;
	if (shell->redir->symbol == APPEND)
		fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0755);
	else
		fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	if (shell->fd_out != STDOUT_FILENO)
	{
		close(shell->fd_out);
		shell->fd_out = fd;
	}
	else
		shell->fd_out = fd;
}
