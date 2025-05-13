#include "minishell.h"

void	ft_add_back(t_tmp_env **lst, t_tmp_env *new)
{
	t_tmp_env	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_last(*lst);
		current->next = new;
	}
}

void	ft_add_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_last_envp(*lst);
		current->next = new;
	}
}

void	ft_add_back_shell(t_shell **lst, t_shell *new)
{
	t_shell	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_last_shell(*lst);
		current->next = new;
	}
}

void	ft_add_front(t_tmp_env **lst, t_tmp_env *new)
{
	new->next = *lst;
	*lst = new;
}
