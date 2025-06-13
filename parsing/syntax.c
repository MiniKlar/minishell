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

int	unexpected_quote(t_shell *shell, t_token *token, char quote)
{
	ft_putstr_fd("bash: syntax error near unexpected quote `", 2);
	ft_putchar_fd(quote, 2);
	ft_putendl_fd("'", 2);
	free_token_struct(token);
	shell->wstatus = 2;
	return (1);
}

bool	is_directory(char character)
{
	if (character == '.' || character == '/')
		return (true);
	else
		return (false);
}

bool	check_syntax(t_shell *shell, t_token *tokens)
{
	if (!tokens)
		return (false);
	if (is_directory(tokens->value[0]))
	{
		if (tokens->value[0] == '.' && tokens->value[1] == '\0')
		{
			ft_putstr_fd("bash: ",2);
			ft_putstr_fd(tokens->value ,2);
			ft_putstr_fd(": filename argument required ",2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd(tokens->value ,2);
			ft_putstr_fd(": usage: . filename [arguments]",2);
			return (false);
		}
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(tokens->value, 2);
			ft_putstr_fd(": Is directory\n", 2);
		}
		return (false);
	}
	if (tokens->value[0] == '|' && tokens->value[1] == '\0')
		return (unexpected_token(shell, tokens->value));
	while (tokens)
	{
		if (is_redirection(tokens) != 0)
		{
			if (is_metacharacter(tokens->value) && tokens->next == NULL)
				return (unexpected_token(shell, NULL));
			if (is_metacharacter(tokens->next->value))
				return (unexpected_token(shell, tokens->next->value));
		}
		if (tokens->value[0] == '|' && tokens->value[1] == '|') //surement creer une boucle a linterieur du char * pour verifier que ya pas doubles pipes
			return (unexpected_token(shell, "||"));
		if (tokens->value[0] == '&' && tokens->value[1] == '&') //surement creer une boucle a linterieur du char * pour verifier que ya pas doubles pipes
			return (unexpected_token(shell, "&&"));
		if (tokens->value[0] == '|' && tokens->value[1] != '\0')
			return (unexpected_token(shell, "|"));
		if (tokens->value[0] == '<' && tokens->value[1] == '>')
			return (unexpected_token(shell, "<>"));
		tokens = tokens->next;
	}
	return (true);
}
