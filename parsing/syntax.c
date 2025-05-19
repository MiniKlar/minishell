#include "../includes/parsing.h"

static int	unexpected_token(char *token)
{
	if (!token)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putendl_fd("'", 2);
	}
	return (0);
}

int	check_syntax(t_token *tokens)
{
    t_token	*current = tokens;
    t_token	*prev = NULL;

    if (!current) return 1;
    
    if (current->value[0] == '|')
        return unexpected_token("|");
    
    while (current)
    {
        if (is_redirection(current))
        {
            if (!current->next || is_metacharacter(current->next->value[0]))
                return unexpected_token(current->next ? current->next->value : "newline");
        }
        if (current->value[0] == '|' && prev && prev->value[0] == '|')
            return unexpected_token("|");
        prev = current;
        current = current->next;
    }
    return 1;
}
