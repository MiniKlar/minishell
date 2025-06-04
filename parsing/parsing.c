#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

bool	parsing(t_shell *shell, char *line)
{
	t_token *raw_tokens;
	t_token *tokens;
	t_token *tmp;

	raw_tokens = tokenisation(shell, line);
	if (!raw_tokens)
		return (false);
	else
	{
		tmp = raw_tokens;
		while (raw_tokens != NULL)
		{
			printf("Voici tokens = [%s]\n", raw_tokens->value);
			raw_tokens = raw_tokens->next;
		}
	}
	raw_tokens = tmp;
	printf("\n --------------------------------------- \n");
	if (!check_syntax(shell, raw_tokens))
	{
		printf("Error syntax \n");
		free_token_struct(raw_tokens);
		return (false);
	}
	tokens = proccess_raw_tokens(raw_tokens);
	free_token_struct(raw_tokens);
	if (!tokens)
		return (false);
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
