#include "minishell.h"

void	open_append_access_outfile(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0755);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
}

void	open_access_outfile(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
}
