#include "minishell.h"

t_redir	*ft_last_redir(t_redir *lst)
{
	t_redir	*tmp;

	if (lst == NULL)
		return (lst);
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

t_tmp_env	*ft_last(t_tmp_env *lst)
{
	t_tmp_env	*tmp;

	if (lst == NULL)
		return (lst);
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

t_envp	*ft_last_envp(t_envp *lst)
{
	t_envp	*tmp;

	if (lst == NULL)
		return (lst);
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

int	ft_size(t_tmp_env *lst)
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

// size_t print_pipes_nbr(t_shell *node)
// {
// 	size_t i;

// 	i = 0;
// 	if (!node)
// 		return (0);
// 	else
// 	{
// 		while (node)
// 		{
// 			if (node->nb_pipe > i)
// 				i = node->nb_pipe;
// 			node = node->next;
// 		}
// 		return (i);
// 	}
// }
