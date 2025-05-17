#include "minishell.h"

int	ft_pwd(t_shell *shell, bool print)
{
	pid_t id_fork;
	id_fork = fork();
	if (id_fork == -1)
		perror("fork");
	if (id_fork == 0)
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
	}
	waitpid(id_fork, &shell->wstatus, 0);
	return (0);
}
