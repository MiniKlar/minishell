#include "minishell.h"

t_shell	*get_shell_context(t_shell *shell)
{
	static t_shell	*saved = NULL;

	if (shell != NULL)
		saved = shell;
	return (saved);
}

void	set_echoctl(int enable)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (enable)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


void sig_handler(int signal)
{
	t_shell *shell;
	
	shell = get_shell_context(NULL);
	if (signal == SIGINT && !g_child_running)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("^C", 0);
		rl_on_new_line();
		rl_redisplay();
		shell->exit_code = 131;
	}
	else if (signal == SIGINT && g_child_running)
		write(STDOUT_FILENO, "\n", 1);
	else if (signal == SIGQUIT)
	{
		if (g_child_running)
		{
			shell->exit_code = 131;
			g_child_running = 0;
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
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
