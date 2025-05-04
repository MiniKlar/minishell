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

void	free_tokens(t_token *node)
{
	t_token	*tmp;

	if (node == NULL)
		return ;
	else
	{
		while (node)
		{
			free(node->tokens);
			tmp = node->next;
			free(node);
			node = tmp;
		}
	}
}

void	free_params(t_params *node)
{
	t_params	*tmp;

	if (node == NULL)
		return ;
	else
	{
		while (node)
		{
			free(node->name);
			free(node->valeur);
			tmp = node->next;
			free(node);
			node = tmp;
		}
	}
}
