#include "minishell.h"

int cd(t_token *tokens, char **envp)
{
	size_t	i;

	i = 0;
	t_token *tmp;

	tmp = tokens;
	while (i != 2)
	{
		tokens = tokens->next;
		i++;
	}
	if (tokens->tokens != NULL)
	{
		printf("Trop d'arguments");
		return (1);
	}
	else
	{
		tokens = tmp;
		tokens = tokens->next;
		if (chdir(tokens->tokens) == -1)
		{
			perror("cd");
			return (1);
		}
		else
		{
			
			printf("Success! You changed the directory\n");
			return (0);
		}
	}
	return (0);
}
