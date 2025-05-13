#include "minishell.h"

t_shell *create_node_token(char *arg, size_t i)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell-> = ft_strdup(arg);
	shell->shell = NULL;
	return (shell);
}

t_shell *fill_token(t_shell *node, char **arg)
{
	t_shell *new_node;
	size_t	i;

	i = 0;
	while (arg[i])
	{
		new_node = create_node_token(arg[i], i + 1);
		ft_add_back_shell(&node, new_node);
		i++;
	}
	find_pipes_heredoc(node);
	return (node);
}

void print_shells(t_shell *node)
{
	if (!node)
		printf("pas de node");
	else
	{
		while (node)
		{
			write(1, node->shell, ft_strlen(node->shell));
			ft_putchar_fd('\n', 1);
			node = node->next;
		}
	}
}
