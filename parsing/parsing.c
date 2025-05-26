#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

t_shell	*parsing(t_shell *shell, char *line)
{
	t_token *tokens;
	t_token *tmp;

	if (!shell || !line)
	{
		printf("!shell || !line \n");
		return (NULL);
	}
	tokens = tokenisation(shell, line);
	if (!tokens)
	{
		printf("!tokens \n");
		return (NULL);
	}
	else
	{
		tmp = tokens;
		while (tokens != NULL)
		{
			printf("Voici tokens = [%s]\n", tokens->value);
			tokens = tokens->next;
		}
	}
	tokens = tmp;
	printf("\n --------------------------------------- \n");
	if (!check_syntax(shell, tokens))
	{
		printf("Error syntax \n");
		free_token_struct(tokens);
		return (NULL);
	}
	shell = parse_tokens(shell, tokens);
	if (!shell)
	{
		printf("!shell PAS REMPLi\n");
		free_token_struct(tokens);
		free_shell(shell);
		return (NULL);
	}
	free_token_struct(tokens);
	return (shell);
}
