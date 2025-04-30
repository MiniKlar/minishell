#include "minishell.h"

int ft_nb_tokens(char *str)
{
	size_t i;
	size_t k;

	i = 0;
	k = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			k++;
		i++;
	}
	return (k);
}

void set_caca(char *str, size_t i, t_token *tokens, size_t depth)
{
	size_t k;
	size_t j;

	j = 0;
	k = i - 1;
	if (str[k] == ')' || depth == 1)
	{
		while((str[k] != ' ' || str[k + 1] != '(' || depth >= 1) && k != 0)
			k--;
	}
	else
	{
		while(str[k] != ' ' && k != 0)
			k--;
	}
	if (strlen(str) == i || k != 0)
		k++;
	tokens->tokens[tokens->nb_tokens] = malloc(sizeof(char) * (i - k + 1));
	while (k != i)
	{
		tokens->tokens[tokens->nb_tokens][j] = str[k];
		j++;
		k++;
	}
	tokens->tokens[tokens->nb_tokens][j] = '\0';
	tokens->nb_tokens++;
}

void	ft_strtok(t_token *tokens, char *str, char delimiter)
{
	size_t i;
	bool parenthesis;
	size_t depth;

	i = 0;
	parenthesis = false;
	depth = 0;
	tokens->nb_tokens = 0;
	tokens->tokens = malloc(sizeof(char *) * (ft_nb_tokens(str) + 1));
	if (!str || !tokens->tokens)
		return ;
	while (str[i])
	{
		if (str[i] == '(')
		{
			parenthesis = true;
			depth++;
		}
		else if (str[i] == delimiter && parenthesis == false)
			set_caca(str, i, tokens, depth);
		else if (str[i] == ')' && parenthesis == true)
		{
			if (depth == 0)
				parenthesis = false;
			depth--;
			i++;
			set_caca(str, i, tokens, depth);
		}
		i++;
	}
	set_caca(str, i, tokens, depth);
	tokens->tokens[tokens->nb_tokens] = NULL;
}

