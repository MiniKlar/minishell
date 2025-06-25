/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:56:11 by lomont            #+#    #+#             */
/*   Updated: 2025/06/25 13:05:02 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_sigint(void)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_child_quit;

	ft_bzero(&sa_ignore, sizeof(sa_ignore));
	sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_ignore, NULL);
	ft_bzero(&sa_child_quit, sizeof(sa_child_quit));
	sa_child_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_child_quit, NULL);
}

void	set_signals_heredoc(void)
{
	struct sigaction	sa_sigint;

	ft_bzero(&sa_sigint, sizeof(sa_sigint));
	sa_sigint.sa_handler = &sigint_handler_heredoc;
	sa_sigint.sa_flags = 0;
	sigaction(SIGINT, &sa_sigint, NULL);
}

void	set_signals_child(void)
{
	struct sigaction	sa_child;
	struct sigaction	sa_child_quit;

	ft_bzero(&sa_child, sizeof(sa_child));
	sa_child.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_child, NULL);
	ft_bzero(&sa_child_quit, sizeof(sa_child_quit));
	sa_child_quit.sa_handler = SIG_IGN;
	sa_child_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_child_quit, NULL);
}

void	set_signals_interactive(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	ft_bzero(&sb, sizeof(sb));
	sb.sa_handler = SIG_IGN;
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}
