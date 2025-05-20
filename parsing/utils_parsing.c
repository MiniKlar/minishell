#include "../includes/parsing.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

// void	free_shell(t_shell *shell)
// {
// 	t_cmd	*cmd;
// 	t_redir	*redir;

// 	while (shell->cmd)
// 	{
// 		cmd = shell->cmd;
// 		shell->cmd = shell->cmd->next;
// 		if (cmd->cmd)
// 		{
// 			for (int i = 0; cmd->cmd[i]; i++)
// 				free(cmd->cmd[i]);
// 			free(cmd->cmd);
// 		}
// 		while (cmd->redir)
// 		{
// 			redir = cmd->redir;
// 			cmd->redir = cmd->redir->next;
// 			free(redir->str);
// 			free(redir);
// 		}
// 		free(cmd);
// 	}
// }

int	syntax_error(const char *msg)
{
	ft_putendl_fd(msg, 2);
	return (0);
}

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

void	token_add_back(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_metacharacter(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ');
}

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	return (
		!ft_strcmp(token->value, "<")
		|| !ft_strcmp(token->value, ">")
		|| !ft_strcmp(token->value, "<<")
		|| !ft_strcmp(token->value, ">>")
	);
}

static void	add_redir(t_redir **redir_list, t_symbol symbol, char *filename)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->symbol = symbol;
	new_redir->str = ft_strdup(filename);
	new_redir->next = NULL;
	if (!*redir_list)
		*redir_list = new_redir;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

int	handle_redirection(t_token **current, t_redir **redir_list)
{
	t_symbol	symbol;

	if (!ft_strcmp((*current)->value, "<"))
		symbol = REDIR_IN;
	else if (!ft_strcmp((*current)->value, ">"))
		symbol = REDIR_OUT;
	else if (!ft_strcmp((*current)->value, "<<"))
		symbol = HERE_DOC;
	else
		symbol = APPEND;
	if (!(*current)->next || !(*current)->next->value)
	{
		ft_putendl_fd("Syntax error: missing redirection target", 2);
		return (0);
	}
	add_redir(redir_list, symbol, (*current)->next->value);
	*current = (*current)->next->next;
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
