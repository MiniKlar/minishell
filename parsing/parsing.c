#include "../includes/parsing.h"

#include "../includes/parsing.h"

int parsing(char *line, t_shell *shell)
{
	t_token *tokens;

	if (!line || !shell)
		return (1);
	shell->cmd = NULL;
	shell->nb_pipe = 0;
	tokens = lexer(line);
	if (!tokens)
		return (1);
	if (!check_syntax(tokens))
	{
		free_tokens(tokens);
		return (1);
	}
	if (!parse_tokens(tokens, shell))
	{
		free_tokens(tokens);
		free_shell(shell);
		return (1);
	}
	free_tokens(tokens);
	return (0);
}
