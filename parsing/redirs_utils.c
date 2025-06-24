#include "minishell.h"

static void	add_redir(t_cmd *cmd, t_symbol symbol, char *filename)
{
	t_redir	*new_redir;
	t_redir	*first_redir;

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
		first_redir = cmd->redir;
		while (cmd->redir->next != NULL)
			cmd->redir = cmd->redir->next;
		cmd->redir->next = new_redir;
		cmd->redir = first_redir;
	}
}

int	handle_redirection(t_token *tokens, t_cmd *cmd)
{
	t_symbol	symbol;

	if (ft_strncmp(tokens->value, "<", 2) == 0)
		symbol = REDIR_IN;
	else if (ft_strncmp(tokens->value, ">", 2) == 0)
		symbol = REDIR_OUT;
	else if (ft_strncmp(tokens->value, "<<", 3) == 0)
		symbol = HERE_DOC;
	else
		symbol = APPEND;
	add_redir(cmd, symbol, tokens->next->value);
	return (2);
}
