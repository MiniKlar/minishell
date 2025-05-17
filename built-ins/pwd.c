#include "minishell.h"

// DANS CHILD

int	ft_pwd(bool print)
{
	char *buffer;
		buffer = malloc(sizeof(char) * 1024);
		if (getcwd(buffer, 1024) == NULL)
			perror("pwd error");
		else
		{
			if (print)
				printf("%s\n", buffer);
		}
		free(buffer);
	return (0);
}
