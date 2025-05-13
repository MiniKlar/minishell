#include "minishell.h"

int ft_exit(t_shell *node)
{
	ft_putstr_fd("exit\n", 1);
	free_shell(node);
	exit(0); //doit exit sur le wstatus ou le exit code de lancienne commande
}
