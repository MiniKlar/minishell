#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

bool	in_quote(char c, char *current_quote)
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

void	add_token(t_token **tokens, char *str, size_t i)
{
	char *tmp;

	tmp = NULL;
	if (i == 0)
		token_add_back(tokens, token_new(ft_strdup(str)));
	else
	{
		tmp = ft_substr(str, 0, i);
		token_add_back(tokens, token_new(ft_strdup(tmp)));
		free(tmp);
	}
}

int	handle_metacharacter(t_token **tokens, char *line, size_t i)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_token(tokens, &line[i], 0);
		return (i + 1);
	}
	else if (line[i] == '<' && line[i + 1] == '<')
	{
		add_token(tokens, &line[i], 0);
		return (i + 1);
	}
	else
	{
		add_token(tokens, &line[i], 0);
		return (i);
	}
}

// void	check_if_token_in_quote(char *line, size_t *i, t_token **tokens,
// 					char *current_quote)
// {
// 	size_t	start;

// 	start = *i;
// 	while ((line[*i] && ((!is_metacharacter(line[*i]) || *current_quote)
// 				&& !ft_isspace(line[*i]))) || *current_quote)
// 	{
// 		in_quote(line[*i], current_quote);
// 		(*i)++;
// 	}
// 	add_token(tokens, line + start, 0);
// }
