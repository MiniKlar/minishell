#include "minishell.h"

int ft_pipe_counter(t_token *node)
{
	size_t current_max_pipes;

	current_max_pipes = 1;
	while (node)
	{
		if (ft_strncmp(node->tokens, "|", ft_strlen(node->tokens)) != 0)
			;
		else if (node->count_pipes == current_max_pipes)
			current_max_pipes = node->count_pipes;
		node = node->next;
	}
	return (current_max_pipes);
}

t_token *create_node_token(char *arg, size_t i)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->tokens = ft_strdup(arg);
	node->nb_tokens = i;
	node->count_pipes = 0;
	node->next = NULL;
	node->is_pipe = false;
	return (node);
}

void	find_pipes_heredoc(t_token *node)
{
	size_t	i;

	i = 0;
	while (node)
	{
		if (ft_strncmp(node->tokens, "|", ft_strlen(node->tokens)) == 0)
		{
			node->count_pipes = ++i;
			node->is_pipe = true;
		}
		node = node->next;
	}
}

t_token *fill_token(t_token *node, char **arg)
{
	t_token *new_node;
	size_t	i;

	i = 0;
	while (arg[i])
	{
		new_node = create_node_token(arg[i], i + 1);
		ft_add_back_tokens(&node, new_node);
		i++;
	}
	find_pipes_heredoc(node);
	return (node);
}

void print_tokens(t_token *node)
{
	if (!node)
		printf("pas de node");
	else
	{
		while (node)
		{
			write(1, node->tokens, ft_strlen(node->tokens));
			ft_putchar_fd('\n', 1);
			node = node->next;
		}
	}
}
