#include "minishell.h"

t_shell	*get_shell_context(t_shell *shell)
{
	static t_shell	*saved;

	if (saved == NULL)
		saved = NULL;
	if (shell != NULL)
		saved = shell;
	return (saved);
}
