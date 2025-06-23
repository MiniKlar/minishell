#include "minishell.h"

void	sigint_handler_child(int signal, t_shell *shell)
{
	if (signal == SIGINT && shell->is_child)
		write(STDOUT_FILENO, "\n", 1);
}

void	sig_handler(int signal)
{
	t_shell	*shell;

	shell = get_shell_context(NULL);
	if (signal == SIGINT && !shell->is_child)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		shell->exit_code = 130;
	}
	sigint_handler_child(signal, shell);
	if (signal == SIGQUIT)
	{
		if (shell->is_child)
			shell->exit_code = 131;
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	set_signals_interactive(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	act.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signals_exec(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signals_default(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
