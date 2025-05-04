#include "minishell.h"

t_params	*ft_last(t_params *lst)
{
	t_params	*tmp;

	if (lst == NULL)
		return (lst);
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

t_token	*ft_last_token(t_token *lst)
{
	t_token	*tmp;

	if (lst == NULL)
		return (lst);
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

int	ft_size(t_params *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

size_t print_pipes_nbr(t_token *node)
{
	size_t i;

	i = 0;
	if (!node)
		return (0);
	else
	{
		while (node)
		{
			if (node->count_pipes > i)
				i = node->count_pipes;
			node = node->next;
		}
		return (i);
	}
}
