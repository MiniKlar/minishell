#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

void	handle_syntax_error(t_shell *shell, t_token **tokens, char c)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('`', 2);
	ft_putchar_fd('\n', 2);
	free_token_struct(*tokens);
	shell->wstatus = 2;
}

bool	unexpected_token(t_shell *shell, char *token)
{
	if (!token)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'",
			2);
		shell->wstatus = 2;
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putendl_fd("'", 2);
		shell->wstatus = 2;
	}
	return (false);
}

int	unexpected_quote(t_shell *shell, t_token *token, char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected quote `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
	free_token_struct(token);
	shell->wstatus = 2;
	return (1);
}

bool	check_syntax(t_shell *shell, t_token *tokens)
{
	t_token *tmp;

	tmp = NULL;
	if (!tokens)
		return (false);
	while (tokens)
	{
		if (is_redirection(tokens) != 0)
		{
			if (is_metacharacter(tokens->value) && tokens->next == NULL)
				return (unexpected_token(shell, NULL));
			if (is_metacharacter(tokens->next->value))
				return (unexpected_token(shell, tokens->next->value));
		}
		if (tokens->value[0] == '|' && tmp && tmp->value[0] == '|')
			return (unexpected_token(shell, "|"));
		tmp = tokens;
		tokens = tokens->next;
	}
	return (true);
}
