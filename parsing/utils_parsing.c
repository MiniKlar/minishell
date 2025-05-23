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
	return (
		ft_strncmp(token->value, "<", ft_strlen(token->value))
		|| ft_strncmp(token->value, ">", ft_strlen(token->value))
		|| ft_strncmp(token->value, "<<", ft_strlen(token->value))
		|| ft_strncmp(token->value, ">>", ft_strlen(token->value)));
}

static void	add_redir(t_cmd *cmd, t_symbol symbol, char *filename)
{
	t_redir	*new_redir;
	t_redir	*tmp;

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
			cmd = cmd->next;
		cmd->next = new_redir;
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
