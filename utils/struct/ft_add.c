#include "minishell.h"

void	ft_add_back(t_params **lst, t_params *new)
{
	t_params	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_last(*lst);
		current->next = new;
	}
}

void	ft_add_front(t_params **lst, t_params *new)
{
	new->next = *lst;
	*lst = new;
}
