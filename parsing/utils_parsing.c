/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpatin <lpatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:21:43 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/23 18:33:16 by lpatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_metacharacter(char *str)
{
	if (str[0] == '|' && str[1] == ' ')
		return (true);
	else if (str[0] == '<' || str[0] == '>')
		return (true);
	else
		return (false);
}

char	find_next_quote(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			break ;
		else
			i++;
	}
	return (line[i]);
}

char	*ft_join_str(char *line, char *to_append)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(line, to_append);
	free(tmp);
	free(to_append);
	return (line);
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

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	else if (ft_strncmp(token->value, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(token->value, ">", 2) == 0)
		return (2);
	else if (ft_strncmp(token->value, "<<", 3) == 0)
		return (3);
	else if (ft_strncmp(token->value, ">>", 3) == 0)
		return (4);
	else if (ft_strncmp(token->value, "<>", 3) == 0)
		return (5);
	else
		return (0);
}

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
