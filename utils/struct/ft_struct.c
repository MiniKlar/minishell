#include "minishell.h"

static 	t_envp	*ft_last_envp(t_envp *lst);
static 	t_redir	*ft_last_redir(t_redir *lst);

void	ft_delone_env(t_envp *lst, char *env_to_find)
{
	t_envp *node_before_env_to_find;
	t_envp *tmp;

	tmp = NULL;
	if (!lst)
		return ;
	else
	{
		while (lst != NULL)
		{
			if (ft_strncmp(lst->envp, env_to_find, ft_strlen(env_to_find)) == 0)
			{
				printf("VOICI ENVP %s\n", lst->envp);
				tmp = lst->next;
				break ;
			}
			node_before_env_to_find = lst;
			lst = lst->next;
		}
		free(lst->envp);
		free(lst);
		node_before_env_to_find->next = tmp;
	}
}

void	ft_add_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_last_redir(*lst);
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

static t_redir	*ft_last_redir(t_redir *lst)
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

static t_envp	*ft_last_envp(t_envp *lst)
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
