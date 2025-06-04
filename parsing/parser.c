#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

void	add_pipe_to_shell(t_shell *shell, t_cmd *cmd)
{
	cmd_add_back(&shell->cmd, cmd);
	shell->nb_pipe++;
}

int	handle_redirection_token(t_token *tokens, t_cmd *cmd)
{
	handle_redirection(tokens, cmd);
	return (0);
}
size_t	find_corresponding_quote(char *line, char quote_to_find)
{
	size_t	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == quote_to_find)
			return (i);
		else
			i++;
	}
	return (0);
}

//int	handle_regular_token(t_shell *shell, t_token **tokens, char *line, bool *in_quote)
//{

//}
