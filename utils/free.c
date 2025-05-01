#include "minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	while (tableau[i] != 0)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}
