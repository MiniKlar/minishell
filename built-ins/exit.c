#include "minishell.h"

int ft_exit(void)
{
	if (kill(0, SIGTERM) == -1)
	{
		perror("Cannot kill shell");
		return (-1);
	}
	else
	{
		printf("\nexit\n");
		return (0);
	}
}
