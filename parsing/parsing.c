#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

int parsing(t_shell *shell, char *line)
{
	t_token *tokens;
	t_token *tmp;

	if (!shell || !line)
		return (1);
	tokens = tokenisation(shell, line);
	if (!tokens)
		return (1);
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
		free_token_struct(tokens);
		return (1);
	}
	if (!parse_tokens(shell, tokens))
	{
		free_token_struct(tokens);
		free_shell(shell);
		return (1);
	}
	free_token_struct(tokens);
	return (0);
}
