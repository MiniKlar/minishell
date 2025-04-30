#include "minishell.h"

int cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	else
	{
		printf("Success! You changed the directory\n");
		return (0);
	}
}
