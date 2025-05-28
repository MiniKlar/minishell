#include "../LIB_SHELL/lib_shell.h"
#include "../includes/parsing.h"

bool	is_metacharacter(char *str)
{
	if ((str[0] == '|' && str[1] == ' ') || str[0] == '<' || str[0] == '>' || str[0] == ' ')
		return (true);
	else
		return (false);
}

t_redir	*create_node_here_redir(char *arg)
{
	t_redir	*shell;

	shell = malloc(sizeof(t_redir));
	if (!shell)
		return (NULL);
	shell->str = ft_strdup(arg);
	shell->symbol = HERE_DOC;
	shell->next = NULL;
	return (shell);
}

t_redir	*create_node_redir(char *arg)
{
	t_redir	*shell;

	shell = malloc(sizeof(t_redir));
	if (!shell)
		return (NULL);
	shell->str = ft_strdup(arg);
	shell->symbol = REDIR_IN;
	shell->next = NULL;
	return (shell);
}

t_redir	*create_node_redir_out(char *arg)
{
	t_redir	*shell;

	shell = malloc(sizeof(t_redir));
	if (!shell)
		return (NULL);
	shell->str = ft_strdup(arg);
	shell->symbol = REDIR_OUT;
	shell->next = NULL;
	return (shell);
}
