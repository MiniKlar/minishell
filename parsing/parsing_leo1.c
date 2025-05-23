#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

int	syntax_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

t_token	*tokenisation(t_shell *shell, char *line)
{
	t_token	*tokens;
	bool	in_quote;
	size_t	i;

	tokens = NULL;
	in_quote = false;
	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '"' || line[i] == '\'') && !in_quote)
			in_quote = true;
		if ((line[i] == ';' || line[i] == '\\') && !in_quote) //si c'est character non gerable
		{
			handle_syntax_error(shell, &tokens, line[i]); //on envoie une erreur
			return (NULL);
		}
		while (line[i] && ft_isspace(line[i]) && !in_quote) //pendant qu'il y a la ligne de commande, que cest isspace et que cest pas une quote, on avance
			i++;
		if (!line[i])
			break ;
		if (is_metacharacter(line) && !in_quote) //si cest un metacharacter et que cest pas une quote
			i = handle_metacharacter(&tokens, line, i); //on gere les metacharacter et on les tokenise
		else
			i += handle_regular_token(shell, &tokens, line + i, &in_quote);
		if (line[i])
			i++;
	}
	return (tokens);
}

int	process_token(t_shell *shell, t_token *tokens, t_cmd command)
{
	if (ft_strncmp(tokens->value, "|", ft_strlen(tokens->value)) == 0)
		shell->nb_pipe++;
	else if (is_redirection(tokens) == 0)
		return (handle_redirection_token(tokens, command));
	else
	{
		shell->cmd->cmd; //finir cette fonction
	}
	return (0);
}

int	parse_tokens(t_shell *shell, t_token *tokens)
{
	t_cmd *command;

	shell->cmd = init_cmd(NULL);
	if (!shell->cmd)
	{
		ft_putstr_fd("Error memory allocation shell->cmd", 2);
		exit(EXIT_FAILURE);
	}
	command = shell->cmd;
	while (tokens)
	{
		if (process_token(shell, tokens, command) == 2) //finir la fonction globale
			tokens->next;
		tokens->next;
	}
	return (0);
}
