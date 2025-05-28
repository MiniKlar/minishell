#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

bool	parsing(t_shell *shell, char *line)
{
	t_token *tokens;
	t_token *tmp;

	tokens = tokenisation(shell, line);
	if (!tokens)
		return (false);
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
		return (false);
	}
	shell = parse_tokens(shell, tokens);
	if (!shell)
	{
		printf("!shell PAS REMPLi\n");
		free_token_struct(tokens);
		free_shell(shell);
		return (false);
	}
	free_token_struct(tokens);
	return (true);
}
