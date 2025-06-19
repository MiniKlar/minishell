#include "minishell.h"

void sig_handler(int signal)
{
	if (signal == SIGINT && !g_child_running)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGINT && g_child_running)
		write(STDOUT_FILENO, "\n", 1);
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void set_signals_interactive(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sig_handler;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void set_signals_exec(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void set_signals_default(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
