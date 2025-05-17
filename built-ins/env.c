#include "minishell.h"

void	ft_env(t_shell *shell)
{
	if (!shell->envp)
		perror("env");
	else
	{
		pid_t id_fork;

		id_fork = fork();
		if (id_fork == -1)
			perror("fork");
		if (id_fork == 0)
			print_tab(shell->envp);
		waitpid(id_fork, &shell->wstatus, 0);
	}
	printf("%d\n", shell->wstatus);
	return ;
}
