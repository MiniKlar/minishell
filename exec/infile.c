#include "minishell.h"

void	open_access_infile(char *str)
{
	int	fd;

	if (access(argv, F_OK) != 0)
	{
		perror("File not accessible");
		exit(EXIT_FAILURE);
	}
	else if (access(argv, R_OK) != 0)
	{
		perror("File not readable");
		exit(EXIT_FAILURE);
	}
	fd = open(argv, O_RDWR);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
}
