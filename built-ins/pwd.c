#include "minishell.h"

char *pwd(void)
{
	char *buffer;

	buffer = malloc(sizeof(char) * 1024);
	if (getcwd(buffer, 1024) == NULL)
		perror("pwd error");
	else
	{
		printf("%s\n", buffer); //peut-etre enlever le \n
		printf("Success!\n");
	}
	return (buffer);
}
