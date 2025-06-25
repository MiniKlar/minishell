#include "minishell.h"

static void	handle_heredoc_sigint(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_done = 1;
}

static int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	heredoc_signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_event;
	sa.sa_handler = handle_heredoc_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

bool	heredoc_wrapper(t_cmd *cmd, int fd)
{
	pid_t	pid;
	int		status;
	static int	sigint_count = 0;

	heredoc_signal_handler();
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		read_heredoc(cmd, fd);
		exit(0);
	}
	else
	{
		close(fd);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			sigint_count++;
			if (sigint_count >= 2)
			{
				sigint_count = 0;
				return (true);
			}
			return (false);
		}
		return (true);
	}
}
