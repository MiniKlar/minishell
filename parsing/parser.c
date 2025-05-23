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
size_t	check_if_last_quote(char *line)
{
	size_t	i;
	size_t	last_quote;

	i = 0;
	last_quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
			last_quote = i;
		i++;
	}
	return (last_quote);
}

int	handle_regular_token(t_shell *shell, t_token **tokens, char *line, bool *in_quote)
{
	size_t	i;
	size_t	index_last_quote;

	i = 0;
	if (*in_quote == true)
	{
		index_last_quote = check_if_last_quote(line);
		i++;
	}
	while (line[i] || *in_quote == true)
	{
		if (ft_isalpha(line[i]) == 0 && line[i] != '\'' && line[i] != '"' && *in_quote == false && line[i] != '|')
			break ;
		else if (*in_quote == true)
		{
			if (i == index_last_quote)
			{
				if (line[0] != line[index_last_quote])
				{
					unexpected_quote(shell, *tokens, line + i);
					return (ft_strlen(line));
				}
				*in_quote = false;
				i++;
				break ;
			}
		}
		i++;
	}
	add_token(tokens, line, i);
	return (i);
}
