#include "minishell.h"

int ft_exit(t_params *node)
{
	ft_putstr_fd("exit\n", 1);
	free_params(node);
	return (0);
}
