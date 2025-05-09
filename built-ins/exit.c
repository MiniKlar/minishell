#include "minishell.h"

int ft_exit(t_token *node)
{
	ft_putstr_fd("exit\n", 1);
	free_tokens(node);
	exit(0); //doit exit sur le wstatus ou le exit code de lancienne commande
}
