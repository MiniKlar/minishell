#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

t_token	*token_new(char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	else if (ft_strncmp(token->value, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(token->value, ">", 2) == 0)
		return (2);
	else if (ft_strncmp(token->value, "<<", 2) == 0)
		return (3);
	else if (ft_strncmp(token->value, ">>", 2) == 0)
		return (4);
	else
		return (0);
}

static void	add_redir(t_cmd *cmd, t_symbol symbol, char *filename)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->symbol = symbol;
	new_redir->str = ft_strdup(filename);
	new_redir->next = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		while (cmd->redir->next != NULL)
			cmd->redir = cmd->redir->next;
		cmd->redir = new_redir;
	}
}

int	handle_redirection(t_token *tokens, t_cmd *cmd)
{
	t_symbol	symbol;

	if (ft_strncmp(tokens->value, "<", ft_strlen(tokens->value)) == 0)
		symbol = REDIR_IN;
	else if (ft_strncmp(tokens->value, ">", ft_strlen(tokens->value)) == 0)
		symbol = REDIR_OUT;
	else if (ft_strncmp(tokens->value, "<<", ft_strlen(tokens->value)) == 0)
		symbol = HERE_DOC;
	else
		symbol = APPEND;
	add_redir(cmd, symbol, tokens->next->value);
	return (2);
}
