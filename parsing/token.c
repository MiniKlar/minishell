#include "minishell.h"

t_redir *create_node_here_redir(char *arg)
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

t_redir *create_node_redir(char *arg)
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

t_redir *create_node_redir_out(char *arg)
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

// t_shell *fill_token(t_shell *node, char **arg)
// {
// 	t_shell *new_node;
// 	size_t	i;

// 	i = 0;
// 	while (arg[i])
// 	{
// 		new_node = create_node_token(arg[i], i + 1);
// 		ft_add_back_shell(&node, new_node);
// 		i++;
// 	}
// 	find_pipes_heredoc(node);
// 	return (node);
// }

// void print_shells(t_shell *node)
// {
// 	if (!node)
// 		printf("pas de node");
// 	else
// 	{
// 		while (node)
// 		{
// 			write(1, node->shell, ft_strlen(node->shell));
// 			ft_putchar_fd('\n', 1);
// 			node = node->next;
// 		}
// 	}
// }
