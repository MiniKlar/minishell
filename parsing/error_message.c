/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:18 by miniklar          #+#    #+#             */
/*   Updated: 2025/06/18 00:32:31 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_syntax_error(t_shell *shell, t_token **tokens, char c)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('`', 2);
	ft_putchar_fd('\n', 2);
	shell->exit_code = 2;
	(void)tokens;
}

bool	unexpected_token(t_shell *shell, char *token)
{
	if (!token)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'",
			2);
		shell->exit_code = 2;
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putendl_fd("'", 2);
		shell->exit_code = 2;
	}
	return (false);
}

int	unexpected_quote(t_shell *shell, char quote)
{
	ft_putstr_fd("bash: syntax error near unexpected quote `", 2);
	ft_putchar_fd(quote, 2);
	ft_putendl_fd("'", 2);
	shell->exit_code = 2;
	return (1);
}
