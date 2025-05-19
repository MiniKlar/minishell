#include "../includes/parsing.h"

static bool	in_quote(char c, char *current_quote)
{
	if (*current_quote == 0 && (c == '\'' || c == '"'))
	{
		*current_quote = c;
		return (true);
	}
	else if (c == *current_quote)
	{
		*current_quote = 0;
		return (true);
	}
	return (*current_quote != 0);
}

static void	add_token(t_token **tokens, char *start, size_t len)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
		return ;
	ft_strlcpy(value, start, len + 1);
	token_add_back(tokens, token_new(value));
}

t_token	*lexer(char *line)
{
	t_token	*tokens;
	char	current_quote;
	size_t	start;
	size_t	i;

	tokens = NULL;
	current_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '\\')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, &line[i], 1);
			ft_putstr_fd("'\n", 2);
			free_tokens(tokens);
			return (NULL);
        }
		while (line[i] && ft_isspace(line[i]) && !current_quote)
			i++;
		if (!line[i])
			break ;
		start = i;
		if (is_metacharacter(line[i]) && !current_quote)
		{
			if (line[i] == '>' && line[i + 1] == '>')
			{
				add_token(&tokens, line + i, 2);
				i += 2;
			}
			else if (line[i] == '<' && line[i + 1] == '<')
			{
				add_token(&tokens, line + i, 2);
				i += 2;
			}
			else
			{
				add_token(&tokens, line + i, 1);
				i++;
			}
		}
		else
		{
			while ((line[i] && 
				((!is_metacharacter(line[i]) || current_quote) 
				&& !ft_isspace(line[i])))
				|| current_quote)
			{
				in_quote(line[i], &current_quote);
				i++;
			}
			add_token(&tokens, line + start, i - start);
		}
	}
	return (tokens);
}
