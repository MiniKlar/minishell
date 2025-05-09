#include "minishell.h"

void env(char **envp)
{
	if (!envp)
		perror("env");
	else
	{
		pid_t id_fork;

		id_fork = fork();
		if (id_fork == -1)
			perror("fork");
		if (id_fork == 0)
		{
			print_tab(envp);
		}
	}
	// finir fonction avec la structure globale pour update le envp correctement.
}
